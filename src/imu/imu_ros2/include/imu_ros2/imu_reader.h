#pragma once

#include "imu_parser.h"
#include "serial_port.h"

#include <cstdint>
#include <string>

class IMUReader {
public:
    IMUReader() = default;
    ~IMUReader() = default;

    // Non-copyable (SerialPort is non-copyable)
    IMUReader(const IMUReader &) = delete;
    IMUReader &operator=(const IMUReader &) = delete;

    // Open serial port. Returns false on failure.
    bool open(const std::string &device, int baud_rate = 921600);

    void close();
    bool isOpen() const;

    // Send IMU configuration (enter settings mode, enable all outputs, save,
    // return to normal mode). Must be called after open().
    bool configure();

    // Register callback for parsed IMU data.
    void setCallback(IMUDataCallback cb);

    // Read and parse available serial data. Returns bytes read, -1 on error.
    // Call in a loop; callback fires for each complete frame.
    int update();

    // Send raw command bytes to IMU.
    bool sendCommand(const uint8_t *cmd, int len);

private:
    SerialPort sp_;
    IMUParser parser_;

    bool enterSettingsMode();
    bool enterNormalMode();
    bool enableAccelOutput();
    bool enableGyroOutput();
    bool enableEulerOutput();
    bool enableQuatOutput();
    bool setOutputUSB();
    bool saveParameters();
};
