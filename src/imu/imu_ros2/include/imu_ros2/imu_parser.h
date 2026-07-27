#pragma once

#include <cstdint>
#include <functional>

struct Vector3 {
    float x, y, z;
};

struct Quaternion {
    float w, x, y, z;
};

struct IMUData {
    uint8_t device_id = 0;
    Vector3 accel{};
    Vector3 gyro{};
    Vector3 euler{};      // roll, pitch, yaw
    Quaternion quat{};

    int updated = 0;      // bitmask: 1=accel, 2=gyro, 4=euler, 8=quat
};

using IMUDataCallback = std::function<void(const IMUData &)>;

class IMUParser {
public:
    IMUParser();

    void setCallback(IMUDataCallback cb);

    // Feed raw bytes from serial port. Calls callback when a full set is ready.
    void feed(const uint8_t *data, int len);

    void reset();

private:
    enum State {
        SYNC1,
        SYNC2,
        ID,
        TYPE,
        DATA,
        CRC1,
        CRC2,
        END_MARKER
    };

    State state_ = SYNC1;
    uint8_t dev_id_ = 0;
    uint8_t frame_type_ = 0;
    uint8_t buf_[64];
    int buf_pos_ = 0;
    int data_len_ = 0;

    IMUData current_data_;
    IMUDataCallback callback_;

    void processFrame();
    int expectedDataLen(uint8_t type) const;
};
