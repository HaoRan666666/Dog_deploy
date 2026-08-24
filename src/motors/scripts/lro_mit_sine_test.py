#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
LRO_CAN 电机 MIT 模式正弦往返测试脚本

功能:
    - 通过 motors_py (pybind11 封装) 创建单个 LRO_CAN 电机
    - 初始化后读取当前编码器位置作为正弦中心
    - 用 MIT 模式让电机位置按正弦曲线往返运动:
          target = pos0 + amplitude * sin(2 * pi * freq * t)

    MIT 控制律 (电机内部执行):
          tau = kp * (p_des - p_actual) + kd * (v_des - v_actual) + tau_ff

用法 (需先 source 工作区, 使 motors_py 进入 PYTHONPATH, 且 CAN 口已 up):
    source /opt/ros/humble/setup.bash          # 或 /opt/ros/jazzy
    source ~/Dog_deploy/install/setup.bash
    # 确保 CAN 口已配置, 例如:
    #   sudo ip link set can0 up type can bitrate 1000000

    python3 lro_mit_sine_test.py --id 1 --can can0
    python3 lro_mit_sine_test.py --id 2 --can can0 --amplitude 0.3 --freq 0.5 --kp 100 --kd 3

参数:
    --id          电机 CAN ID (默认 1)
    --can         CAN 接口名 (默认 can0)
    --model       电机型号: 0=5550 1=6562 2=8462 3=10062 (默认 2)
    --zero-offset 编码器零点软件补偿 rad (默认 0)
    --amplitude   正弦幅值 rad (默认 0.3)
    --freq        正弦频率 Hz (默认 0.5)
    --kp          位置刚度 (默认 100)
    --kd          速度阻尼 (默认 3)
    --dt          控制周期 s (默认 0.005 = 200Hz)
    --duration    运行时长 s (默认 0 = 直到 Ctrl+C)
"""

import argparse
import math
import signal
import sys
import time

try:
    import motors_py
except ImportError:
    print("找不到 motors_py 模块，请先 source 工作区: "
          "source ~/Dog_deploy/install/setup.bash", file=sys.stderr)
    sys.exit(1)


def main():
    parser = argparse.ArgumentParser(
        description="LRO_CAN 电机 MIT 模式正弦往返测试")
    parser.add_argument("--id", type=int, default=1, help="电机 CAN ID (默认 1)")
    parser.add_argument("--can", type=str, default="can0", help="CAN 接口名 (默认 can0)")
    parser.add_argument("--model", type=int, default=2,
                        help="电机型号: 0=5550 1=6562 2=8462 3=10062 (默认 2)")
    parser.add_argument("--zero-offset", type=float, default=0.0,
                        help="编码器零点软件补偿 rad (默认 0)")
    parser.add_argument("--amplitude", type=float, default=0.3,
                        help="正弦幅值 rad (默认 0.3)")
    parser.add_argument("--freq", type=float, default=0.5,
                        help="正弦频率 Hz (默认 0.5)")
    parser.add_argument("--kp", type=float, default=100.0,
                        help="位置刚度 (默认 100)")
    parser.add_argument("--kd", type=float, default=3.0,
                        help="速度阻尼 (默认 3)")
    parser.add_argument("--dt", type=float, default=0.005,
                        help="控制周期 s (默认 0.005 = 200Hz)")
    parser.add_argument("--duration", type=float, default=0.0,
                        help="运行时长 s (默认 0 = 直到 Ctrl+C)")
    args = parser.parse_args()

    if args.amplitude <= 0:
        print("振幅 amplitude 必须 > 0", file=sys.stderr)
        sys.exit(1)

    print(f"创建电机: id={args.id}, can={args.can}, type=LRO_CAN, "
          f"model={args.model}, zero_offset={args.zero_offset}")
    motor = motors_py.MotorDriver.create_motor(
        motor_id=args.id,
        interface_type="can",      # LRO_CAN 驱动不使用此参数
        interface=args.can,
        motor_type="LRO_CAN",
        motor_model=args.model,
        master_id_offset=0,        # LRO_CAN 驱动不使用此参数
        motor_zero_offset=args.zero_offset,
    )

    # 初始化: 失能 → 设 MIT 模式 → 使能 → 读状态(触发首个回包) → 检查错误码
    err = motor.init_motor()
    if err != 0:
        print(f"电机初始化失败: error_id=0x{err:x}", file=sys.stderr)
        sys.exit(1)
    print(f"电机初始化成功 (can={motor.get_can_name()}, id={motor.get_motor_id()})")

    # 等待首个回包到达, 读取当前编码器位置作为正弦中心
    time.sleep(0.05)
    pos0 = motor.get_motor_pos()
    print(f"当前位置 (正弦中心): {pos0:.4f} rad")

    # Ctrl+C / SIGTERM 平滑停机
    running = True

    def on_stop(signum, frame):
        nonlocal running
        running = False

    signal.signal(signal.SIGINT, on_stop)
    signal.signal(signal.SIGTERM, on_stop)

    t0 = time.monotonic()
    next_log = 0.0
    print("开始正弦往返 (Ctrl+C 停止)...")
    try:
        while running:
            t = time.monotonic() - t0
            target = pos0 + args.amplitude * math.sin(2.0 * math.pi * args.freq * t)
            # MIT 指令: (目标位置, 目标速度, kp, kd, 前馈力矩)
            # v_des=0, tau_ff=0, 由 kp/kd 做位置跟踪
            motor.motor_mit_cmd(target, 0.0, args.kp, args.kd, 0.0)

            if t >= next_log:
                cur = motor.get_motor_pos()
                print(f"t={t:6.2f}s  target={target:+.4f} rad  "
                      f"pos={cur:+.4f} rad  err={target - cur:+.4f}")
                next_log += 0.5

            if args.duration > 0 and t >= args.duration:
                break
            time.sleep(args.dt)
    finally:
        print("\n去使能电机...")
        motor.deinit_motor()
        print("已安全停机")


if __name__ == "__main__":
    main()
