// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Luo1imasi
//
// IMUDriver — IMU 硬件抽象层 (与旧 roboparty_imu 接口兼容)
// 底层使用 IMUReader 驱动串口通信, 后台线程持续读取 IMU 数据。

#pragma once

#include <memory>
#include <string>
#include <vector>

class IMUDriver {
   public:
    virtual ~IMUDriver() = default;

    // 读取姿态四元数 [w, x, y, z]
    virtual std::vector<float> get_quat() = 0;

    // 读取角速度 [ωx, ωy, ωz] (rad/s)
    virtual std::vector<float> get_ang_vel() = 0;

    // 工厂方法 — 创建具体 IMU 驱动实例
    //
    // 参数:
    //   id:             IMU 设备 ID (CAN ID, 串口模式下忽略)
    //   interface_type: "serial" / "can"
    //   interface:      串口路径 "/dev/ttyUSB0" 或 CAN 接口 "can0"
    //   type:           IMU 型号 ("HIPNUC", "Wit" — 当前实现通用)
    //   baudrate:       串口波特率 (CAN 模式下忽略)
    static std::shared_ptr<IMUDriver> create_imu(int id,
                                                  const std::string& interface_type,
                                                  const std::string& interface,
                                                  const std::string& type,
                                                  int baudrate);
};
