#include "imu_reader.h"

#include <chrono>
#include <cstdio>
#include <thread>

bool IMUReader::open(const std::string &device, int baud_rate) {
    return sp_.open(device, baud_rate);
}

void IMUReader::close() {
    sp_.close();
}

bool IMUReader::isOpen() const {
    return sp_.isOpen();
}

void IMUReader::setCallback(IMUDataCallback cb) {
    parser_.setCallback(std::move(cb));
}

int IMUReader::update() {
    uint8_t buf[4096];
    int n = sp_.read(buf, sizeof(buf));
    if (n < 0) return -1;
    if (n > 0) {
        parser_.feed(buf, n);
    }
    return n;
}

bool IMUReader::sendCommand(const uint8_t *cmd, int len) {
    return sp_.write(cmd, len) == len;
}

// ─── IMU configuration commands ───

bool IMUReader::enterSettingsMode() {
    uint8_t cmd[] = {0xAA, 0x06, 0x01, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::enterNormalMode() {
    uint8_t cmd[] = {0xAA, 0x06, 0x00, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::enableAccelOutput() {
    uint8_t cmd[] = {0xAA, 0x01, 0x14, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::enableGyroOutput() {
    uint8_t cmd[] = {0xAA, 0x01, 0x15, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::enableEulerOutput() {
    uint8_t cmd[] = {0xAA, 0x01, 0x16, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::enableQuatOutput() {
    uint8_t cmd[] = {0xAA, 0x01, 0x17, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::setOutputUSB() {
    uint8_t cmd[] = {0xAA, 0x0A, 0x00, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::saveParameters() {
    uint8_t cmd[] = {0xAA, 0x03, 0x01, 0x0D};
    return sendCommand(cmd, sizeof(cmd));
}

bool IMUReader::configure() {
    using namespace std::chrono_literals;

    if (!enterSettingsMode()) {
        fprintf(stderr, "IMUReader: enter settings mode failed\n");
        return false;
    }
    std::this_thread::sleep_for(100ms);

    if (!enableAccelOutput())  { fprintf(stderr, "IMUReader: enable accel failed\n"); return false; }
    std::this_thread::sleep_for(20ms);
    if (!enableGyroOutput())   { fprintf(stderr, "IMUReader: enable gyro failed\n"); return false; }
    std::this_thread::sleep_for(20ms);
    if (!enableEulerOutput())  { fprintf(stderr, "IMUReader: enable euler failed\n"); return false; }
    std::this_thread::sleep_for(20ms);
    if (!enableQuatOutput())   { fprintf(stderr, "IMUReader: enable quat failed\n"); return false; }
    std::this_thread::sleep_for(20ms);

    if (!setOutputUSB())       { fprintf(stderr, "IMUReader: set USB output failed\n"); return false; }
    std::this_thread::sleep_for(20ms);

    if (!saveParameters())     { fprintf(stderr, "IMUReader: save parameters failed\n"); return false; }
    std::this_thread::sleep_for(100ms);

    if (!enterNormalMode())    { fprintf(stderr, "IMUReader: enter normal mode failed\n"); return false; }
    std::this_thread::sleep_for(100ms);

    return true;
}
