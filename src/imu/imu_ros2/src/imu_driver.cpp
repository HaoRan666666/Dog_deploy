// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Luo1imasi

#include "imu_driver.hpp"

#include <atomic>
#include <chrono>
#include <mutex>
#include <stdexcept>
#include <thread>

#include "imu_reader.h"

// ============================================================================
// SerialImuDriver — 串口 IMU 驱动 (封装 IMUReader + 后台读取线程)
//
// 与旧 HIPNUC/Wit 驱动的行为一致:
//   - 构造时打开串口、配置 IMU、启动后台线程
//   - 后台线程持续 update() → 回调更新缓存
//   - get_quat() / get_ang_vel() 返回最新缓存值 (线程安全)
// ============================================================================
class SerialImuDriver : public IMUDriver {
   public:
    SerialImuDriver(const std::string& device, int baud_rate)
        : running_(false) {
        if (!reader_.open(device, baud_rate)) {
            throw std::runtime_error("IMUDriver: failed to open " + device);
        }
        if (!reader_.configure()) {
            reader_.close();
            throw std::runtime_error("IMUDriver: failed to configure IMU on " + device);
        }

        reader_.setCallback([this](const IMUData& data) {
            std::lock_guard<std::mutex> lock(mutex_);
            cached_quat_    = {data.quat.w, data.quat.x, data.quat.y, data.quat.z};
            cached_ang_vel_ = {data.gyro.x, data.gyro.y, data.gyro.z};
        });

        running_ = true;
        thread_ = std::thread([this]() {
            while (running_) {
                reader_.update();
                std::this_thread::sleep_for(std::chrono::microseconds(500));
            }
        });
    }

    ~SerialImuDriver() override {
        running_ = false;
        if (thread_.joinable()) thread_.join();
        reader_.close();
    }

    std::vector<float> get_quat() override {
        std::lock_guard<std::mutex> lock(mutex_);
        return cached_quat_;
    }

    std::vector<float> get_ang_vel() override {
        std::lock_guard<std::mutex> lock(mutex_);
        return cached_ang_vel_;
    }

   private:
    IMUReader reader_;
    std::thread thread_;
    std::mutex mutex_;
    std::atomic<bool> running_;
    std::vector<float> cached_quat_{0.f, 0.f, 0.f, 0.f};
    std::vector<float> cached_ang_vel_{0.f, 0.f, 0.f};
};

// ============================================================================
// 工厂方法 — 根据 interface_type 创建对应的驱动实例
// ============================================================================
std::shared_ptr<IMUDriver> IMUDriver::create_imu(int /*id*/,
                                                  const std::string& interface_type,
                                                  const std::string& interface,
                                                  const std::string& /*type*/,
                                                  int baudrate) {
    if (interface_type == "serial") {
        return std::make_shared<SerialImuDriver>(interface, baudrate);
    }
    throw std::runtime_error("IMUDriver: unsupported interface_type: " + interface_type);
}
