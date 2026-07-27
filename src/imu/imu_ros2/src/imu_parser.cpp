#include "imu_parser.h"
#include "crc16.h"

#include <cstdio>
#include <cstring>

IMUParser::IMUParser() {
    reset();
}

void IMUParser::setCallback(IMUDataCallback cb) {
    callback_ = std::move(cb);
}

void IMUParser::reset() {
    state_ = SYNC1;
    buf_pos_ = 0;
    data_len_ = 0;
    frame_type_ = 0;
    dev_id_ = 0;
    current_data_ = IMUData{};
}

int IMUParser::expectedDataLen(uint8_t type) const {
    switch (type) {
        case 0x01: return 12; // accel (AccX, AccY, AccZ)
        case 0x02: return 12; // gyro (GyroX, GyroY, GyroZ)
        case 0x03: return 12; // euler (Roll, Pitch, Yaw)
        case 0x04: return 16; // quaternion (W, X, Y, Z)
        default:   return 0;
    }
}

// USB frame format: 55 AA ID TYPE [DATA] CRC16 0A
void IMUParser::feed(const uint8_t *data, int len) {
    for (int i = 0; i < len; ++i) {
        uint8_t byte = data[i];

        switch (state_) {
        case SYNC1:
            if (byte == 0x55) {
                state_ = SYNC2;
            }
            break;

        case SYNC2:
            if (byte == 0xAA) {
                state_ = ID;
            } else if (byte != 0x55) {
                state_ = SYNC1;
            }
            break;

        case ID:
            dev_id_ = byte;
            state_ = TYPE;
            break;

        case TYPE:
            frame_type_ = byte;
            data_len_ = expectedDataLen(byte);
            if (data_len_ == 0) {
                state_ = SYNC1;
            } else {
                buf_pos_ = 0;
                state_ = DATA;
            }
            break;

        case DATA:
            buf_[buf_pos_++] = byte;
            if (buf_pos_ >= data_len_) {
                state_ = CRC1;
            }
            break;

        case CRC1:
            buf_[buf_pos_++] = byte; // CRC low byte
            state_ = CRC2;
            break;

        case CRC2:
            buf_[buf_pos_++] = byte; // CRC high byte
            state_ = END_MARKER;
            break;

        case END_MARKER:
            if (byte == 0x0A) {
                processFrame();
            }
            state_ = SYNC1;
            break;
        }
    }
}

void IMUParser::processFrame() {
    // CRC is little-endian: low byte first
    uint16_t received_crc = buf_[data_len_] | (buf_[data_len_ + 1] << 8);

    // Scope: ID + TYPE + DATA
    uint8_t scope1[20];
    scope1[0] = dev_id_;
    scope1[1] = frame_type_;
    memcpy(scope1 + 2, buf_, data_len_);

    // Scope: TYPE + DATA
    uint8_t scope2[20];
    scope2[0] = frame_type_;
    memcpy(scope2 + 1, buf_, data_len_);

    // Scope: 55 AA + ID + TYPE + DATA
    uint8_t scope4[24];
    scope4[0] = 0x55;
    scope4[1] = 0xAA;
    scope4[2] = dev_id_;
    scope4[3] = frame_type_;
    memcpy(scope4 + 4, buf_, data_len_);

    struct { const uint8_t *ptr; int len; } tests[] = {
        {scope1, 2 + data_len_},
        {scope2, 1 + data_len_},
        {buf_,   data_len_},
        {scope4, 4 + data_len_},
    };

    bool matched = false;
    for (auto &t : tests) {
        if (crc16_compute(t.ptr, t.len) == received_crc ||
            crc16_v1(t.ptr, t.len) == received_crc) {
            matched = true;
            break;
        }
    }
    if (!matched) {
        uint16_t swapped = (received_crc << 8) | (received_crc >> 8);
        for (auto &t : tests) {
            if (crc16_compute(t.ptr, t.len) == swapped ||
                crc16_v1(t.ptr, t.len) == swapped) {
                matched = true;
                break;
            }
        }
    }

    if (!matched) return;

    current_data_.device_id = dev_id_;

    switch (frame_type_) {
    case 0x01: // Accel (g), three floats little-endian
        memcpy(&current_data_.accel.x, buf_ + 0, 4);
        memcpy(&current_data_.accel.y, buf_ + 4, 4);
        memcpy(&current_data_.accel.z, buf_ + 8, 4);
        current_data_.updated |= 1;
        break;

    case 0x02: // Gyro (°/s)
        memcpy(&current_data_.gyro.x, buf_ + 0, 4);
        memcpy(&current_data_.gyro.y, buf_ + 4, 4);
        memcpy(&current_data_.gyro.z, buf_ + 8, 4);
        current_data_.updated |= 2;
        break;

    case 0x03: // Euler (°): Roll, Pitch, Yaw
        memcpy(&current_data_.euler.x, buf_ + 0, 4);
        memcpy(&current_data_.euler.y, buf_ + 4, 4);
        memcpy(&current_data_.euler.z, buf_ + 8, 4);
        current_data_.updated |= 4;
        break;

    case 0x04: // Quaternion: W, X, Y, Z
        memcpy(&current_data_.quat.w, buf_ + 0,  4);
        memcpy(&current_data_.quat.x, buf_ + 4,  4);
        memcpy(&current_data_.quat.y, buf_ + 8,  4);
        memcpy(&current_data_.quat.z, buf_ + 12, 4);
        current_data_.updated |= 8;
        break;
    }

    if (callback_) {
        callback_(current_data_);
    }
    current_data_.updated = 0;
}
