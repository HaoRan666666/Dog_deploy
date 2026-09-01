# 安全部署测试流程（部署前逐模块验证）

> 目标：在四轮足机器人（wheel_quad）正式整机落地运行 RL 策略之前，
> 按「无硬件 → 单模块 → 空载推理 → 架起 → 落地」的顺序逐级验证，
> 每一步通过后才进入下一步，把硬件/配置/策略问题在最小范围内暴露出来。

> 配合文档：[CM5_BUILD.md](CM5_BUILD.md)（构建与环境）、[README.md](README.md)（项目总览）。

---

## 0. 安全总原则

1. **永远先架起再通电测试**：任何电机使能前，机器人必须离地架起（四轮/四腿悬空），防止上电瞬间电机乱动导致倾覆或夹伤。
2. **随时能断电**：测试时手上/脚边始终有急停手段——手柄 **B 键**（失能电机）、**Ctrl+C** 杀掉节点、或直接断 CAN 主控电源。
3. **一次只测一个变量**：单电机阶段一次只动一个关节，确认接线/ID/方向后再动下一个。
4. **速度由低到高**：整机落地后用最小速度指令起步，逐步放大。

---

## 1. 阶段 0：环境与构建自检

在 CM5 板上，确认以下全部就绪（详细见 [CM5_BUILD.md](CM5_BUILD.md)）：

```bash
# 1) 构建产物存在（三个包都已编译）
ls install/                     # 应有 damiao_imu / motors / inference 相关目录

# 2) 实时权限（SCHED_FIFO / mlockall 需要 root）
sudo -E true                    # sudo 可用
ulimit -r                       # 期望 >= 1（rtprio）；为 0 则见 CM5_BUILD.md §5 实时性

# 3) 串口权限（IMU 用 /dev/ttyACM0）
id                              # 期望在 dialout 组
ls -l /dev/ttyACM0              # 确认 IMU 设备存在（插上 IMU 后）

# 4) CAN 口已建（can0~can3）
ip link show | grep can         # 期望看到 can0 can1 can2 can3 且 state UP
```

**CAN 建口命令**（若未建，每条总线分别执行）：

```bash
sudo ip link set can0 up type can bitrate 1000000
sudo ip link set can1 up type can bitrate 1000000
sudo ip link set can2 up type can bitrate 1000000
sudo ip link set can3 up type can bitrate 1000000
```

> ⚠️ CAN 口名（can0~can3）是 Linux 接口名，由 `ip link` / 设备树决定，不在代码里。
> 若硬件实际枚举为 can1~can4，需同步改 [robot.yaml](src/inference/robots/wheel_quad/robot.yaml) 的 `motor_interface`（见 [CM5_BUILD.md](CM5_BUILD.md) §5）。

---

## 2. 阶段 1：IMU 独立验证（不接电机、不跑推理）

目的：确认 IMU 驱动、串口、数据格式正确，四元数/角速度有合理数值。

```bash
source /opt/ros/humble/setup.bash
source ~/Dog_deploy/install/setup.bash

ros2 launch damiao_imu damiao_imu.launch.py device:=/dev/ttyACM0
# 另开终端
ros2 topic echo /imu/data_raw
```

**验收标准**：
- 能看到四元数 `orientation` 和角速度 `angular_velocity` 持续刷新；
- 静止时角速度接近 0，四元数模长 ≈ 1（`w²+x²+y²+z² ≈ 1`）；
- 用手转动 IMU，四元数/角速度随之变化，方向符合右手定则。

> 若打不开：`ls /dev/ttyACM*` 确认设备号，检查 `dialout` 组权限。

---

## 3. 阶段 2：CAN + 单电机验证（逐电机）

目的：确认每条 CAN 总线的 ID 编址、电机类型、方向、编码器读数正确。

### 3.1 关节电机（LRO_CAN，髋/大腿/小腿）正弦往返测试

```bash
source ~/Dog_deploy/install/setup.bash

# 依次测每个关节电机（ID 1~4，can0~can3，model 2=8462）
sudo -E python3 src/motors/scripts/lro_mit_sine_test.py --id 1 --can can0 --model 2 --amplitude 0.2 --freq 0.5 --kp 100 --kd 3
```

**验收标准**：
- 电机按正弦小幅往返（**机器人保持架起**，关节悬空）；
- 打印的位置读数连续、无跳变（±π 翻转除外）；
- 每个关节依次测完，记录「ID ↔ 物理关节」对应关系，与 [robot.yaml](src/inference/robots/wheel_quad/robot.yaml) 的 `motor_id` 布局核对。

### 3.2 轮电机（LINGZU，速度控制）

> 轮电机用灵足 LINGZU 驱动，暂无独立正弦测试脚本；可通过单电机示例
> `scripts/motors_py_example.py` 改造，或直接在推理节点的站立/速度指令阶段验证。
> 验证重点：轮子能转动、方向正确、编码器读数合理。

### 3.3 电机标零（可选，走「硬件标零」路线时）

```bash
sudo -E python3 scripts/set_zero.py
```

> ⚠️ 注意：
> 1. 当前 [set_zero.yaml](scripts/config/set_zero.yaml) 是 23 电机 DM 旧配置，**不是 wheel_quad**，需先改成 16 电机 + `LRO_CAN`/`LINGZU`；
> 2. `set_motor_zero()` 可能未写 Flash，断电后零点可能丢失，需确认是否要补 `write_motor_flash()`；
> 3. 若已在 [robot.yaml](src/inference/robots/wheel_quad/robot.yaml) 用 `motor_zero_offset` 做软件补偿，则硬件标零与软件补偿**二选一**，不要混用。

---

## 4. 阶段 3：手柄验证（可脱离机器人单独做）

目的：确认手柄连接、按键/摇杆索引与方向符号，与 [ros_interface.cpp](src/inference/src/ros_interface.cpp) 的映射一致。

```bash
ros2 run joy joy_node                 # 不带 device_name，SDL 自动认第一个手柄
ros2 topic echo /joy                  # 另开终端，按键看 buttons[] / axes[]
```

**实测映射（wheel_quad，左推为正）**：

| 物理操作 | 数组下标 | 功能 |
|---|---|---|
| A | `buttons[0]` | 站立复位 |
| B | `buttons[1]` | 电机初始化/失能 |
| X | `buttons[3]` | 推理启动/暂停 |
| Y | `buttons[4]` | 控制源切换（手柄 ↔ /cmd_vel）|
| LB | `buttons[6]` | 中断模式切换 |
| 左摇杆上下 | `axes[0]` | vx（前进/后退）|
| 左摇杆左右 | `axes[1]`（左推 +）| vy（左右平移）|
| 右摇杆左右 | `axes[2]`（左推 +）| wz（转向）|

**验收标准**：
- 每个按键按下时对应下标变 `1`、松开变 `0`；
- 摇杆方向与符号与上表一致（**前推 vx 的正负需实测确认**，见 [ros_interface.cpp:246](src/inference/src/ros_interface.cpp#L246)）。

> 多机器人同网段时，每台设独立 `ROS_DOMAIN_ID` 或用话题 remap 隔离（避免互相收到别人的手柄）。

---

## 5. 阶段 4：推理节点空载启动（不启动推理）

目的：确认推理节点能启动、ONNX 加载成功、硬件初始化正常。

```bash
source /opt/ros/humble/setup.bash
source ~/Dog_deploy/install/setup.bash

sudo -E ros2 launch roboparty_inference inference.launch.py robot:=wheel_quad
```

**验收标准**：
- 节点启动无异常、无 `Exception caught: ...`（注意：**IMU 必须插着**，否则启动时 `Failed to open serial port: /dev/ttyACM0` 直接退出）；
- 终端打印出参数（obs 布局、模型名、关节默认角度等）和手柄提示；
- 打印出 `Press 'B' ... / 'A' ... / 'X' ...` 等操作提示。

**然后（机器人保持架起）依次验证**：
1. 按 **B** → 电机使能（`Motors initialized`）；
2. 按 **A** → 站立复位（`Stand up completed`），关节平滑过渡到默认姿态；
3. 检查 `ros2 topic echo /joint_states` 是否持续发布关节状态；
4. 再次按 **B** → 电机失能（`Motors deinitialized`）。

---

## 6. 阶段 5：架起 + 启动推理（不落地）

目的：验证策略前向推理正常、观测合理、动作有限（无 NaN/Inf/突变）。

> ⚠️ **机器人必须架起离地**，四轮悬空，防止策略输出异常时电机带动机器人失控。

1. 重复阶段 4：启动节点 → B 使能 → A 站立；
2. 按 **X** 启动推理（`Inference started`）；
3. 观察：

```bash
ros2 topic echo /action          # 策略输出（速度/位置指令），检查数值
ros2 topic echo /joint_states    # 关节实际状态
```

**验收标准**：
- `/action` 数值在合理范围（关节位置 ±0.5 rad 量级、轮速 ±5 rad/s 量级，受 `clip_actions`/`action_scales` 约束）；
- **无 NaN / Inf / 大幅突变**（前后两帧跳变超过量级）；
- 关节没有高频抖动或持续打满限位。

> ⚠️ 现状限制：观测 `obs` 目前**没有发布成话题**，无法直接 `echo` 检查。若要做严格的「obs 正常性 + action 有限性」空跑，需要先在代码里加 `/obs` 话题发布 + `isfinite` 守卫（`output_enabled` dry-run 模式）。在此之前，只能通过 `/action`、`/joint_states` 和日志间接判断。

---

## 7. 阶段 6：整机落地（逐步放权）

目的：从站立到受控运动，逐步确认闭环控制与安全机制。

**建议顺序**：

1. **落地站立**：机器人放下，四轮着地 → B 使能 → A 站立，观察是否稳定站立；
2. **手柄小速度**：按 X 启动推理，手柄给最小速度指令（慢速前进/后退/平移/转向），确认方向正确；
3. **速度放大**：逐步加大指令，确认跟踪与稳定性；
4. **摔倒/异常**：故意触发，确认安全机制生效。

**方向核对（落地后必查）**：
- 前推左摇杆 → 前进（若后退，改 [ros_interface.cpp:246](src/inference/src/ros_interface.cpp#L246) 符号）；
- 左推左摇杆 → 左移；左推右摇杆 → 左转（与训练 REP-103 约定一致，无需翻转）。

**随时应急**：
- 按 **A** → 立即回到站立复位；
- 按 **B** → 立即失能所有电机；
- `Ctrl+C` → 节点退出，`node.reset()` 会 join 线程并释放硬件。

---

## 8. 安全机制核对表

部署前确认以下保护均已生效（来源：[default.yaml](src/inference/robots/wheel_quad/configs/default.yaml)）：

| 机制 | 位置/参数 | 作用 | 需确认 |
|---|---|---|---|
| 关节软限位 | `joint_limits` | 位置指令 clamp 到 [lower, upper] | 与 URDF `<limit>` 一致 |
| 倒地检测 | `gravity_z_upper: -0.5` | `gravity_b.z > -0.5` 判定倒地 → 急停 | 架起/落地时阈值合理 |
| 电机离线检测 | `offline_threshold`（默认 25）| 电机无响应计数超限 → 保护 | ARM 上可能需调大 |
| 动作限幅 | `clip_actions: 150` | 原始动作 clamp | 与训练 `clip_actions` 对齐 |
| 观测限幅 | `clip_observations: 150` | 观测 clamp | — |
| 指令限幅 | `clip_cmd` | 手柄/cmd_vel 限幅 | vx/vy/wz 范围合理 |
| 动作平滑 | `act_alpha: 0.9` | EMA 平滑输出 | 无突变 |
| 电机驱动限位 | 驱动层（motors 包）| 电机侧限位 | 驱动参数正确 |

---

## 9. 常见问题速查

| 现象 | 原因 | 处理 |
|---|---|---|
| 启动即退出 `Failed to open serial port` | IMU 没插/路径错/没权限 | 插 IMU、`ls /dev/ttyACM*`、加 dialout 组 |
| `Failed to set realtime priority` | rtprio=0 / 无 CAP_SYS_NICE | `sudo -E` 启动，或 setcap/limits.conf |
| 链接报 `x86-64` | onnxruntime x64 污染 | `rm -rf src/inference/thirdparty/onnxruntime` 重建 |
| 电机无响应 | CAN 口没 up / ID 错 / 接线错 | `ip link show`、核对 `motor_id`、单电机测试 |
| 手柄没反应 | joy_node 没起 / 不在同域 / 映射错 | 阶段 3 逐项核对 |
| 推理 action 有 NaN/Inf | 模型/观测异常 | 回阶段 5，检查 obs/模型 |

---

## 10. 附加：用 ROS2 Service 脚本化验证（替代手柄，可自动化）

> 阶段 4/5 里「按 B 使能 → 按 A 站立 → 按 X 启动推理」这一串手柄操作，
> 都能用推理节点内置的 ROS2 Service 完成。优点：可写进脚本、无人工误操作、
> 每步有明确的 `success/message` 返回值可断言，适合部署前做脚本化验收。

### 10.1 Service 清单（全部为 `std_srvs/srv/Trigger`，无参数）

| Service | 功能 | 对应手柄 |
|---|---|---|
| `/init_motors` | 使能 16 个电机 | B（初始化） |
| `/deinit_motors` | 失能所有电机 | B（再按一次） |
| `/stand_up` | 平滑插值站立复位 | A |
| `/reset_joints` | 直接跳回默认姿态（降 KP 防冲击，不插值） | — |
| `/start_inference` | 启动策略推理 | X |
| `/stop_inference` | 暂停策略推理 | X（再按一次） |
| `/set_zeros` | 硬件标零 | —（或走 `scripts/set_zero.py`） |
| `/clear_errors` | 清除电机故障 | — |
| `/refresh_joints` | 主动刷新电机状态 | — |
| `/read_joints` | 读关节并发布 `/joint_states` | — |
| `/read_imu` | 读 IMU 并发布 `/imu` | — |

### 10.2 调用语法

```bash
ros2 service list
ros2 service type /init_motors          # 期望 std_srvs/srv/Trigger

# 通用格式（所有 service 一致）
ros2 service call /init_motors std_srvs/srv/Trigger "{}"
# → success: true, message: "Motors initialized successfully"
```

**前置约束**（来源：[ros_interface.cpp](src/inference/src/ros_interface.cpp) 各回调）：

- `stand_up` / `reset_joints` / `set_zeros` 要求**推理已停止**，否则返回 `Inference is running, cannot ...`；
- 所有电机操作要求**先 `init_motors`**，否则返回 `Motors are not initialized, ...`；
- `init_motors` / `start_inference` 有幂等保护，重复调用返回 `already ...`。

### 10.3 脚本化验收流程（架起状态，对应阶段 4/5）

```bash
# A. 节点空载启动后，先验 IMU
ros2 service call /read_imu std_srvs/srv/Trigger "{}"
ros2 topic echo /imu            # 四元数/角速度刷新、模长≈1

# B. 使能电机 + 读关节
ros2 service call /init_motors std_srvs/srv/Trigger "{}"     # success: true
ros2 service call /read_joints std_srvs/srv/Trigger "{}"
ros2 topic echo /joint_states    # 16 关节持续发布

# C. 站立复位（平滑插值，约 3s）
ros2 service call /stand_up std_srvs/srv/Trigger "{}"        # 3s 后 success: true

# D. 启停推理（仍架起，观察 /action）
ros2 service call /start_inference std_srvs/srv/Trigger "{}"
ros2 topic echo /action          # 无 NaN/Inf/突变
ros2 service call /stop_inference std_srvs/srv/Trigger "{}"

# E. 收尾
ros2 service call /deinit_motors std_srvs/srv/Trigger "{}"
ros2 service call /clear_errors std_srvs/srv/Trigger "{}"
```

### 10.4 一键脚本模板（verify_modules.sh）

```bash
#!/usr/bin/env bash
set -euo pipefail
SRV() { ros2 service call "$1" std_srvs/srv/Trigger "{}"; }

echo "== IMU ==";          SRV /read_imu
echo "== init motors ==";  SRV /init_motors
echo "== read joints ==";  SRV /read_joints
echo "== stand up ==";     SRV /stand_up
echo "== start infer ==";  SRV /start_inference
sleep 2
echo "== stop infer ==";   SRV /stop_inference
echo "== deinit ==";       SRV /deinit_motors
echo "== clear errors =="; SRV /clear_errors
```

> ⚠️ 每步注意看返回的 `success:` 是否为 `true`；为 `false` 时看 `message` 定位原因。
> `stand_up` / `start_inference` 期间机器人必须保持架起离地，确认 `/action`、`/joint_states` 无异常后再进入阶段 6 落地。

---

> 本文档是「整机落地前」的安全验证基线。新增或改动硬件/策略/驱动后，应回到对应阶段重新验证。
