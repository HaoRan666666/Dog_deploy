#include "lingzu_motor_driver.hpp"

// ── 灵足电机型号参数表（位置/速度/力矩量程、KP/KD 上限） ──
// 与 LRO 电机 lro_can_limit_param[] 结构一致，按 motor_model 索引切换。
Lingzu_Limit_Param lingzu_limit_param[LINGZU_Num_Of_Motor] = {
    {12.57f, 50.0f,  6.0f, 500.0f, 5.0f},   // LINGZU_EL05
    {12.57f, 44.0f, 17.0f, 500.0f, 5.0f},   // LINGZU_RS02
};

LingzuMotorDriver::LingzuMotorDriver(uint16_t motor_id, const std::string& can_interface,
                                     uint16_t host_can_id, LingzuMotorModel motor_model,
                                     double motor_zero_offset)
    : MotorDriver(), motor_model_(motor_model) {
    comm_type_ = CommType::CAN;
    motor_id_ = motor_id;
    motor_control_mode_ = NONE;

    // 型号越界时回退到 RS02，避免数组越界
    if (motor_model_ < 0 || motor_model_ >= LINGZU_Num_Of_Motor) {
        logger_->warn("Unknown Lingzu motor model: {} (ID: {}), fallback to RS02",
                      static_cast<int>(motor_model_), motor_id_);
        motor_model_ = LINGZU_RS02;
    }
    limit_param_ = lingzu_limit_param[motor_model_];

    can_interface_ = can_interface;
    motor_zero_offset_ = motor_zero_offset;
    host_can_id_ = (host_can_id == 0) ? LINGZU_DEFAULT_HOST_ID : (host_can_id & 0x7FF);

    can_ = MotorsCAN::get(can_interface);

    CanCbkFunc can_callback = std::bind(&LingzuMotorDriver::can_rx_cbk, this, std::placeholders::_1);
    can_->add_can_callback(can_callback, host_can_id_.load());
}

LingzuMotorDriver::~LingzuMotorDriver() {
    can_->remove_can_callback(host_can_id_.load());
}

void LingzuMotorDriver::lock_motor() {
    send_special_cmd(0xFF, LINGZU_CMD_ENABLE);
}

void LingzuMotorDriver::unlock_motor() {
    send_special_cmd(0xFF, LINGZU_CMD_DISABLE);
}

uint8_t LingzuMotorDriver::init_motor() {
    unlock_motor();
    Timer::sleep_for(normal_sleep_time);
    set_motor_control_mode(MIT);
    Timer::sleep_for(normal_sleep_time);
    lock_motor();
    Timer::sleep_for(normal_sleep_time);
    refresh_motor_status();
    Timer::sleep_for(normal_sleep_time);
    return error_id_;
}

void LingzuMotorDriver::deinit_motor() {
    unlock_motor();
    Timer::sleep_for(normal_sleep_time);
}

bool LingzuMotorDriver::write_motor_flash() {
    send_special_cmd(0xFF, LINGZU_CMD_SAVE);
    return true;
}

bool LingzuMotorDriver::set_motor_zero() {
    set_motor_zero_lingzu();
    Timer::sleep_for(setup_sleep_time);
    refresh_motor_status();
    Timer::sleep_for(setup_sleep_time);
    logger_->info("motor_id: {0}\tposition: {1}", motor_id_, get_motor_pos());
    unlock_motor();
    if (get_motor_pos() > judgment_accuracy_threshold || get_motor_pos() < -judgment_accuracy_threshold) {
        logger_->warn("set zero error");
        return false;
    } else {
        logger_->info("set zero success");
        return true;
    }
}

void LingzuMotorDriver::can_rx_cbk(const can_frame& rx_frame) {
    response_count_ = 0;

    if (rx_frame.can_dlc < 0x08) return;

    uint8_t rx_motor_id = rx_frame.data[0];
    if (rx_motor_id != motor_id_) return;

    if (expect_fault_response_.exchange(false)) {
        uint32_t fault = static_cast<uint32_t>(rx_frame.data[1])
                       | (static_cast<uint32_t>(rx_frame.data[2]) << 8)
                       | (static_cast<uint32_t>(rx_frame.data[3]) << 16)
                       | (static_cast<uint32_t>(rx_frame.data[4]) << 24);
        fault_bits_ = fault;
        error_id_ = fault == 0 ? 0x00 : 0x01;
        return;
    }

    uint16_t pos_int = (static_cast<uint16_t>(rx_frame.data[1]) << 8) | rx_frame.data[2];
    uint16_t spd_int = (static_cast<uint16_t>(rx_frame.data[3]) << 4) | ((rx_frame.data[4] >> 4) & 0x0F);
    uint16_t t_int   = (static_cast<uint16_t>(rx_frame.data[4] & 0x0F) << 8) | rx_frame.data[5];

    motor_pos_ =
        range_map(pos_int, uint16_t(0), bitmax<uint16_t>(16), -limit_param_.PosMax, limit_param_.PosMax)
        + static_cast<float>(motor_zero_offset_);
    motor_spd_ =
        range_map(spd_int, uint16_t(0), bitmax<uint16_t>(12), -limit_param_.SpdMax, limit_param_.SpdMax);
    motor_current_ =
        range_map(t_int, uint16_t(0), bitmax<uint16_t>(12), -limit_param_.TauMax, limit_param_.TauMax);

    motor_state_ = (rx_frame.data[6] >> 6) & 0x03;
    error_id_ = (rx_frame.data[6] & 0x20) ? 0x01 : 0x00;
    warning_ = (rx_frame.data[6] & 0x10) != 0;

    // Byte6[3-0] + Byte7: 绕组温度 * 10 (°C)
    uint16_t temp_int = (static_cast<uint16_t>(rx_frame.data[6] & 0x0F) << 8) | rx_frame.data[7];
    motor_temperature_ = static_cast<float>(temp_int) / 10.0f;
}

void LingzuMotorDriver::get_motor_param(uint8_t param_cmd) {
    read_register_lingzu(param_cmd);
}

void LingzuMotorDriver::motor_pos_cmd(float pos, float spd, bool ignore_limit) {
    (void)ignore_limit;
    if (motor_control_mode_ != POS) {
        set_motor_control_mode(POS);
        return;
    }
    union32_t pos_val, spd_val;
    pos_val.f = static_cast<float>(pos - motor_zero_offset_);
    spd_val.f = std::abs(spd);

    can_frame tx_frame;
    tx_frame.can_id = (LINGZU_MODE_POS_CAN << 8) | (motor_id_ & 0x7F);
    tx_frame.can_dlc = 0x08;

    tx_frame.data[0] = pos_val.buf[0];
    tx_frame.data[1] = pos_val.buf[1];
    tx_frame.data[2] = pos_val.buf[2];
    tx_frame.data[3] = pos_val.buf[3];
    tx_frame.data[4] = spd_val.buf[0];
    tx_frame.data[5] = spd_val.buf[1];
    tx_frame.data[6] = spd_val.buf[2];
    tx_frame.data[7] = spd_val.buf[3];

    can_->transmit(tx_frame);
    response_count_++;
}

void LingzuMotorDriver::motor_spd_cmd(float spd) {
    if (motor_control_mode_ != SPD) {
        set_motor_control_mode(SPD);
        return;
    }
    union32_t spd_val, cur_val;
    spd_val.f = spd;
    cur_val.f = limit_param_.TauMax;  // 默认电流限制 = 最大力矩

    can_frame tx_frame;
    tx_frame.can_id = (LINGZU_MODE_SPD_CAN << 8) | (motor_id_ & 0x7F);
    tx_frame.can_dlc = 0x08;

    tx_frame.data[0] = spd_val.buf[0];
    tx_frame.data[1] = spd_val.buf[1];
    tx_frame.data[2] = spd_val.buf[2];
    tx_frame.data[3] = spd_val.buf[3];
    tx_frame.data[4] = cur_val.buf[0];
    tx_frame.data[5] = cur_val.buf[1];
    tx_frame.data[6] = cur_val.buf[2];
    tx_frame.data[7] = cur_val.buf[3];

    can_->transmit(tx_frame);
    response_count_++;
}

void LingzuMotorDriver::motor_mit_cmd(float f_p, float f_v, float f_kp, float f_kd, float f_t) {
    f_p -= static_cast<float>(motor_zero_offset_);
    f_p = limit(f_p, -limit_param_.PosMax, limit_param_.PosMax);
    f_v = limit(f_v, -limit_param_.SpdMax, limit_param_.SpdMax);
    f_kp = limit(f_kp, 0.0f, limit_param_.OKpMax);
    f_kd = limit(f_kd, 0.0f, limit_param_.OKdMax);
    f_t = limit(f_t, -limit_param_.TauMax, limit_param_.TauMax);

    uint16_t p  = range_map(f_p,  -limit_param_.PosMax, limit_param_.PosMax, uint16_t(0), bitmax<uint16_t>(16));
    uint16_t v  = range_map(f_v,  -limit_param_.SpdMax, limit_param_.SpdMax, uint16_t(0), bitmax<uint16_t>(12));
    uint16_t kp = range_map(f_kp, 0.0f, limit_param_.OKpMax, uint16_t(0), bitmax<uint16_t>(12));
    uint16_t kd = range_map(f_kd, 0.0f, limit_param_.OKdMax, uint16_t(0), bitmax<uint16_t>(12));
    uint16_t t  = range_map(f_t,  -limit_param_.TauMax, limit_param_.TauMax, uint16_t(0), bitmax<uint16_t>(12));

    can_frame tx_frame;
    tx_frame.can_id = (LINGZU_MODE_MIT_CAN << 8) | (motor_id_ & 0x7F);
    tx_frame.can_dlc = 0x08;

    tx_frame.data[0] = (p >> 8) & 0xFF;
    tx_frame.data[1] = p & 0xFF;
    tx_frame.data[2] = (v >> 4) & 0xFF;
    tx_frame.data[3] = ((v & 0x0F) << 4) | ((kp >> 8) & 0x0F);
    tx_frame.data[4] = kp & 0xFF;
    tx_frame.data[5] = (kd >> 4) & 0xFF;
    tx_frame.data[6] = ((kd & 0x0F) << 4) | ((t >> 8) & 0x0F);
    tx_frame.data[7] = t & 0xFF;

    can_->transmit(tx_frame);
    response_count_++;
}

void LingzuMotorDriver::motor_mit_cmd(float* f_p, float* f_v, float* f_kp, float* f_kd, float* f_t) {
    if (!f_p || !f_v || !f_kp || !f_kd || !f_t) {
        return;
    }

    for (uint8_t slot = 0; slot < 8; ++slot) {
        float p_f  = limit(f_p[slot] - static_cast<float>(motor_zero_offset_), -limit_param_.PosMax, limit_param_.PosMax);
        float v_f  = limit(f_v[slot], -limit_param_.SpdMax, limit_param_.SpdMax);
        float kp_f = limit(f_kp[slot], 0.0f, limit_param_.OKpMax);
        float kd_f = limit(f_kd[slot], 0.0f, limit_param_.OKdMax);
        float t_f  = limit(f_t[slot], -limit_param_.TauMax, limit_param_.TauMax);

        uint16_t p  = range_map(p_f,  -limit_param_.PosMax, limit_param_.PosMax, uint16_t(0), bitmax<uint16_t>(16));
        uint16_t v  = range_map(v_f,  -limit_param_.SpdMax, limit_param_.SpdMax, uint16_t(0), bitmax<uint16_t>(12));
        uint16_t kp = range_map(kp_f, 0.0f, limit_param_.OKpMax, uint16_t(0), bitmax<uint16_t>(12));
        uint16_t kd = range_map(kd_f, 0.0f, limit_param_.OKdMax, uint16_t(0), bitmax<uint16_t>(12));
        uint16_t t  = range_map(t_f,  -limit_param_.TauMax, limit_param_.TauMax, uint16_t(0), bitmax<uint16_t>(12));

        can_frame tx_frame;
        tx_frame.can_id = (LINGZU_MODE_MIT_CAN << 8) | (motor_id_ & 0x7F);
        tx_frame.can_dlc = 0x08;

        tx_frame.data[0] = (p >> 8) & 0xFF;
        tx_frame.data[1] = p & 0xFF;
        tx_frame.data[2] = (v >> 4) & 0xFF;
        tx_frame.data[3] = ((v & 0x0F) << 4) | ((kp >> 8) & 0x0F);
        tx_frame.data[4] = kp & 0xFF;
        tx_frame.data[5] = (kd >> 4) & 0xFF;
        tx_frame.data[6] = ((kd & 0x0F) << 4) | ((t >> 8) & 0x0F);
        tx_frame.data[7] = t & 0xFF;

        can_->transmit(tx_frame);
    }
    response_count_++;
}

void LingzuMotorDriver::set_motor_control_mode(uint8_t motor_control_mode) {
    uint8_t lingzu_mode = LINGZU_MODE_MIT;
    if (!map_control_mode(motor_control_mode, lingzu_mode)) {
        logger_->error("Invalid motor control mode: {} (ID: {})", motor_control_mode, motor_id_);
        return;
    }

    uint8_t old_mode = motor_control_mode_;
    logger_->info("Switching motor control mode: {} -> {} (ID: {})", old_mode, motor_control_mode, motor_id_);

    send_special_cmd(lingzu_mode, LINGZU_CMD_SET_MODE);
    Timer::sleep_for(normal_sleep_time);

    motor_control_mode_ = motor_control_mode;
}

void LingzuMotorDriver::set_motor_id(uint8_t old_id, uint8_t new_id) {
    if (old_id > 0x7F || new_id > 0x7F) {
        logger_->error("Invalid ID range: old={}, new={}", old_id, new_id);
        return;
    }

    if (old_id == new_id) {
        logger_->warn("Skipping ID set: Old and New ID are identical ({})", old_id);
        return;
    }

    logger_->info("Changing Motor ID: {} -> {} (Interface: {})", old_id, new_id, can_interface_);

    can_frame tx_frame{};
    tx_frame.can_id = old_id & 0x7F;
    tx_frame.can_dlc = 0x08;

    memset(tx_frame.data, 0xFF, 6);
    tx_frame.data[6] = new_id & 0x7F;
    tx_frame.data[7] = LINGZU_CMD_SET_ID;

    can_->transmit(tx_frame);
    response_count_++;

    Timer::sleep_for(setup_sleep_time);
    motor_id_ = new_id;
    logger_->info("Set ID command sent. Verify the new ID via bus query.");
}

void LingzuMotorDriver::reset_motor_id() {
    // 灵足 MIT 协议无专用复位 ID 指令，直接设回默认 0x01
    set_motor_id(motor_id_, 0x01);
}

void LingzuMotorDriver::set_motor_zero_lingzu() {
    send_special_cmd(0xFF, LINGZU_CMD_SET_ZERO);
}

void LingzuMotorDriver::clear_motor_error_lingzu() {
    send_special_cmd(0xFF, LINGZU_CMD_CLEAR_ERROR);
}

void LingzuMotorDriver::read_motor_error_lingzu() {
    expect_fault_response_ = true;
    send_special_cmd(0x00, LINGZU_CMD_CLEAR_ERROR);
}

void LingzuMotorDriver::send_special_cmd(uint8_t f_cmd, uint8_t cmd) {
    can_frame tx_frame{};
    tx_frame.can_id = motor_id_ & 0x7F;
    tx_frame.can_dlc = 0x08;

    memset(tx_frame.data, 0xFF, 6);
    tx_frame.data[6] = f_cmd;
    tx_frame.data[7] = cmd;

    can_->transmit(tx_frame);
    response_count_++;
}

void LingzuMotorDriver::set_local_host_can_id(uint16_t host_can_id) {
    host_can_id &= 0x7FF;
    uint16_t old_host_id = host_can_id_.load();
    if (host_can_id == old_host_id) return;

    can_->remove_can_callback(old_host_id);
    CanCbkFunc can_callback = std::bind(&LingzuMotorDriver::can_rx_cbk, this, std::placeholders::_1);
    can_->add_can_callback(can_callback, host_can_id);
    host_can_id_ = host_can_id;
}

void LingzuMotorDriver::write_register_lingzu(uint16_t index, float value) {
    uint8_t* vbuf = reinterpret_cast<uint8_t*>(&value);

    can_frame tx_frame;
    tx_frame.can_id = (LINGZU_MODE_WRITE_CAN << 8) | (motor_id_ & 0x7F);
    tx_frame.can_dlc = 0x08;

    tx_frame.data[0] = index & 0xFF;
    tx_frame.data[1] = (index >> 8) & 0xFF;
    tx_frame.data[2] = 0x00;
    tx_frame.data[3] = 0x00;
    tx_frame.data[4] = vbuf[0];
    tx_frame.data[5] = vbuf[1];
    tx_frame.data[6] = vbuf[2];
    tx_frame.data[7] = vbuf[3];

    can_->transmit(tx_frame);
    response_count_++;
}

void LingzuMotorDriver::read_register_lingzu(uint16_t index) {
    can_frame tx_frame;
    tx_frame.can_id = (LINGZU_MODE_READ_CAN << 8) | (motor_id_ & 0x7F);
    tx_frame.can_dlc = 0x08;

    tx_frame.data[0] = index & 0xFF;
    tx_frame.data[1] = (index >> 8) & 0xFF;
    tx_frame.data[2] = 0x00;
    tx_frame.data[3] = 0x00;
    tx_frame.data[4] = 0x00;
    tx_frame.data[5] = 0x00;
    tx_frame.data[6] = 0x00;
    tx_frame.data[7] = 0x00;

    can_->transmit(tx_frame);
    response_count_++;
}

bool LingzuMotorDriver::map_control_mode(uint8_t motor_control_mode, uint8_t& lingzu_mode) const {
    switch (motor_control_mode) {
        case MIT:
            lingzu_mode = LINGZU_MODE_MIT;
            return true;
        case POS:
            lingzu_mode = LINGZU_MODE_POS;
            return true;
        case SPD:
            lingzu_mode = LINGZU_MODE_SPD;
            return true;
        default:
            return false;
    }
}

void LingzuMotorDriver::refresh_motor_status() {
    motor_mit_cmd(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void LingzuMotorDriver::clear_motor_error() {
    clear_motor_error_lingzu();
}

void LingzuMotorDriver::read_motor_error() {
    read_motor_error_lingzu();
}

void LingzuMotorDriver::set_motor_protocol(uint8_t protocol) {
    if (protocol > LINGZU_PROTOCOL_MIT) {
        logger_->error("Invalid Lingzu protocol: {} (ID: {})", protocol, motor_id_);
        return;
    }
    send_special_cmd(protocol, LINGZU_CMD_SET_PROTOCOL);
}

void LingzuMotorDriver::set_host_can_id(uint8_t host_id) {
    send_special_cmd(host_id, LINGZU_CMD_SET_HOST_ID);
    set_local_host_can_id(host_id);
}

void LingzuMotorDriver::set_active_report(bool enable) {
    send_special_cmd(enable ? 1 : 0, LINGZU_CMD_ACTIVE_REPORT);
}
