#pragma once

#include <atomic>
#include <string>

#include "motor_driver.hpp"
#include "protocol/can_iso.hpp"
#include "utils.hpp"

// 灵足(RobStride)电机默认主机(master) CAN ID —— 正常回包以该 ID 返回
constexpr uint16_t LINGZU_DEFAULT_HOST_ID = 0xFD;

// ── 灵足电机型号（通过 motor_model 选择量程参数） ──
// 位置量程统一 ±12.57 rad，kp 0~500，kd 0~5；差异在速度/力矩量程。
enum LingzuMotorModel {
    LINGZU_EL05 = 0,   // EL05：速度 ±50 rad/s，力矩 ±6 Nm
    LINGZU_RS02 = 1,   // RS02：速度 ±44 rad/s，力矩 ±17 Nm
    LINGZU_Num_Of_Motor
};

// 灵足电机 MIT 协议指令（Byte7 魔数）
enum LingzuCmd : uint8_t {
    LINGZU_CMD_ENABLE        = 0xFC,  // 指令1: 电机使能
    LINGZU_CMD_DISABLE       = 0xFD,  // 指令2: 电机停止
    LINGZU_CMD_SET_ZERO      = 0xFE,  // 指令4: 设置零点
    LINGZU_CMD_CLEAR_ERROR   = 0xFB,  // 指令5: 清除错误/读取异常状态
    LINGZU_CMD_SET_MODE      = 0xFC,  // 指令6: 设置运行模式(由 data[6] 区分)
    LINGZU_CMD_SET_ID        = 0xFA,  // 指令7: 修改电机 CAN ID
    LINGZU_CMD_SET_PROTOCOL  = 0xFD,  // 指令8: 切换电机协议
    LINGZU_CMD_SET_HOST_ID   = 0x01,  // 指令9: 修改主机 CAN ID
    LINGZU_CMD_SAVE          = 0xF8,  // 指令12: 保存电机数据
    LINGZU_CMD_ACTIVE_REPORT = 0xF9   // 指令13: 主动上报开关
};

// 灵足电机运行模式（配合指令6 使用）
enum LingzuMode : uint8_t {
    LINGZU_MODE_MIT = 0,  // MIT 阻抗控制(默认)
    LINGZU_MODE_POS = 1,  // 位置模式(CSP)
    LINGZU_MODE_SPD = 2,  // 速度模式
};

enum LingzuProtocol : uint8_t {
    LINGZU_PROTOCOL_PRIVATE = 0,
    LINGZU_PROTOCOL_CANOPEN = 1,
    LINGZU_PROTOCOL_MIT = 2,
};

enum LingzuMotorState : uint8_t {
    LINGZU_STATE_RESET = 0,
    LINGZU_STATE_CALI = 1,
    LINGZU_STATE_MOTOR = 2,
};

// 灵足电机 CAN ID 位布局（标准 11 位帧）
// bit10~8: 模式类型(0=MIT, 1=POS, 2=SPD, 3=READ, 4=WRITE)
// bit7~0:  电机 CAN ID
constexpr uint8_t LINGZU_MODE_MIT_CAN   = 0;
constexpr uint8_t LINGZU_MODE_POS_CAN   = 1;
constexpr uint8_t LINGZU_MODE_SPD_CAN   = 2;
constexpr uint8_t LINGZU_MODE_READ_CAN  = 3;
constexpr uint8_t LINGZU_MODE_WRITE_CAN = 4;

// 灵足电机量程参数（按型号查表，见 lingzu_motor_driver.cpp）
typedef struct {
    float PosMax;   // 最大位置 (rad)
    float SpdMax;   // 最大速度 (rad/s)
    float TauMax;   // 最大力矩 (Nm)
    float OKpMax;   // 最大 Kp
    float OKdMax;   // 最大 Kd
} Lingzu_Limit_Param;

class LingzuMotorDriver : public MotorDriver {
   public:
    LingzuMotorDriver(uint16_t motor_id, const std::string& can_interface,
                      uint16_t host_can_id, LingzuMotorModel motor_model,
                      double motor_zero_offset = 0.0);
    ~LingzuMotorDriver();

    virtual void lock_motor() override;
    virtual void unlock_motor() override;
    virtual uint8_t init_motor() override;
    virtual void deinit_motor() override;
    virtual bool set_motor_zero() override;
    virtual bool write_motor_flash() override;
    virtual void get_motor_param(uint8_t param_cmd) override;

    virtual void motor_pos_cmd(float pos, float spd, bool ignore_limit) override;
    virtual void motor_spd_cmd(float spd) override;
    virtual void motor_mit_cmd(float f_p, float f_v, float f_kp, float f_kd, float f_t) override;
    virtual void motor_mit_cmd(float* f_p, float* f_v, float* f_kp, float* f_kd, float* f_t) override;
    virtual void set_motor_control_mode(uint8_t motor_control_mode) override;
    virtual int get_response_count() const override {
        return response_count_;
    }
    virtual void set_motor_id(uint8_t old_id, uint8_t new_id) override;
    virtual void reset_motor_id() override;
    virtual void refresh_motor_status() override;
    virtual void clear_motor_error() override;

    void set_motor_protocol(uint8_t protocol);
    void set_host_can_id(uint8_t host_id);
    uint16_t get_host_can_id() const { return host_can_id_.load(); }
    void set_active_report(bool enable);
    void read_motor_error();
    uint32_t get_fault_bits() const { return fault_bits_; }
    uint8_t get_motor_state() const { return motor_state_; }
    bool get_motor_warning() const { return warning_; }

   private:
    std::atomic<int> response_count_{0};
    LingzuMotorModel motor_model_;
    Lingzu_Limit_Param limit_param_;
    std::atomic<uint8_t> motor_state_{0};
    std::atomic<bool> warning_{false};
    std::atomic<uint32_t> fault_bits_{0};
    std::atomic<bool> expect_fault_response_{false};
    std::atomic<uint16_t> host_can_id_{LINGZU_DEFAULT_HOST_ID};

    void set_motor_zero_lingzu();
    void clear_motor_error_lingzu();
    void read_motor_error_lingzu();
    void send_special_cmd(uint8_t f_cmd, uint8_t cmd);
    void set_local_host_can_id(uint16_t host_can_id);
    void write_register_lingzu(uint16_t index, float value);
    void read_register_lingzu(uint16_t index);
    bool map_control_mode(uint8_t motor_control_mode, uint8_t& lingzu_mode) const;

    virtual void can_rx_cbk(const can_frame& rx_frame);
    std::shared_ptr<MotorsCAN> can_;
};
