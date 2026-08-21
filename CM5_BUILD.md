# 香橙派 CM5 项目重建流程

> Dog_deploy —— ROS2 Humble + ONNX Runtime 四轮足强化学习推理部署
> 目标平台：Orange Pi CM5（RK3588，**aarch64**，Ubuntu 22.04 + ROS2 Humble）

---

## 0. 概述

| 项 | 说明 |
|----|------|
| 平台 | Orange Pi CM5（RK3588，ARM64 / aarch64） |
| 系统 | Ubuntu 22.04（jammy） |
| ROS2 | Humble |
| Python | 3.10 |
| 三个包 | `damiao_imu`（IMU 驱动）、`roboparty_motors`（电机驱动）、`roboparty_inference`（推理节点） |
| 依赖关系 | `inference` → `motors` + `damiao_imu`（**构建顺序不能反**） |

代码已自动适配 ARM64：`src/inference/thirdparty/CMakeLists.txt` 会根据
`CMAKE_SYSTEM_PROCESSOR` 自动选择 aarch64 版 ONNX Runtime，且 aarch64 的
tarball（`onnxruntime-linux-aarch64-1.21.0.tgz`）已经随 git 仓库一起分发，
**无需联网下载**。模型文件（`policy_flat.onnx` 等）也都在 git 里。

> 注：本仓库开发机是 Ubuntu 24.04 + Jazzy，三个包均用 C++17 编写，Jazzy 与
> Humble 的 rclcpp API 差异不影响本仓库使用；主要差异是 Python 3.12→3.10、
> fmt 9→8（见 §5）。

---

## 1. 一次性环境准备

### 1.1 安装 ROS2 Humble

参考官方文档在 Ubuntu 22.04 上安装（推荐 `ros-humble-desktop`，自带
`sensor_msgs` / `geometry_msgs` / `std_srvs` 等通用接口包）。

### 1.2 安装系统依赖

```bash
sudo apt update
sudo apt install -y \
    libeigen3-dev \
    libfmt-dev \
    libboost-system-dev \
    pybind11-dev \
    python3-dev \
    zlib1g-dev \
    ccache
```

> - `libfmt-dev` 在 22.04 上是 **fmt 8.1**，本仓库使用的 `fmt::fmt` target
>   fmt 8 起即支持，可直接用（无需降级改动）。
> - `spdlog` 由 ROS2 自带的 `spdlog_vendor` 提供，无需单独安装。
> - `pybind11-dev` + `python3-dev`（3.10）满足 pybind11 编译。

### 1.3 串口权限（IMU 用）

```bash
sudo usermod -a -G dialout $USER
# 重新登录后生效
```

---

## 2. 获取代码

### 2.1 干净检出（推荐）

```bash
git clone https://github.com/HaoRan666666/Dog_deploy.git
cd Dog_deploy
```

### 2.2 ⚠️ 如果用 scp/rsync 拷贝（必须清理）

> 开发机是 x86_64，`src/inference/thirdparty/onnxruntime/lib/` 里已解压的是
> **x86-64** 的 `libonnxruntime.so`。这个解压目录不在 git 里，但如果你直接拷贝
> 整个目录，CMake 会误认为已经解压过、**跳过重新解压，最终链接 x64 库导致失败**。

拷贝后、构建前必须删除：

```bash
rm -rf src/inference/thirdparty/onnxruntime
```

---

## 3. 干净重建

```bash
source /opt/ros/humble/setup.bash
cd ~/Dog_deploy

# 1) 清空旧的构建产物
rm -rf build install log

# 2) 先构建两个底层库（inference 依赖它们）
colcon build --packages-select damiao_imu roboparty_motors

# 3) 再构建推理节点
source install/setup.bash
colcon build --packages-select roboparty_inference
```

- 首次构建会解压 onnxruntime + 编译 yaml-cpp / cnpy，CM5 上约 15～30 分钟。
- 可用 `--parallel-workers 8` 提速。
- 若要用 `rosdep` 装依赖，见 §5 的「package.xml 隐患」——需先修复后才能 `rosdep install` 通过。

---

## 4. 验证

```bash
source /opt/ros/humble/setup.bash
source ~/Dog_deploy/install/setup.bash

# 4.1 先单独验证 IMU（确认设备路径，通常 /dev/ttyACM0）
ros2 launch damiao_imu damiao_imu.launch.py device:=/dev/ttyACM0
ros2 topic echo /imu/data_raw

# 4.2 启动推理（SCHED_FIFO 实时调度需要 root）
sudo -E ros2 launch roboparty_inference inference.launch.py robot:=wheel_quad
```

---

## 5. CM5（22.04 + Humble）特有注意事项

| 项 | 说明 |
|----|------|
| **ROS 版本** | Ubuntu 22.04 + **Humble**（非 Jazzy） |
| **Python** | 3.10（Humble 默认），pybind11 自动匹配 |
| **fmt** | 22.04 自带 fmt 8.1，`fmt::fmt` 目标可用，无需改动 |
| **ONNX Runtime** | aarch64 tarball 已内置并自动选中；预编译二进制 glibc 2.28+ 兼容，Ubuntu 22.04（glibc 2.35）可用 |
| **x64 污染** | 见 2.2，拷贝方式迁移时必须删 `thirdparty/onnxruntime/` |
| **实时性** | `SCHED_FIFO` 需要 root；建议刷 `linux-image-rt`；ARM 上 `offline_threshold_`（默认 25）可能要调大 |
| **CAN 接口** | CM5 的 CAN 设备编号可能不是 `can0`，需对照 `robots/wheel_quad/robot.yaml` 里的 `motor_interface` |
| **串口** | IMU 用 `/dev/ttyACM0`（换口需改 `robot.yaml` 的 `imu_interface`） |
| **内存** | 推理 + `mlockall()` 锁内存，建议 CM5 8/16GB 版本 |

### ⚠️ package.xml 隐患（`roboparty_imu` 拼写错误）

`src/inference/package.xml` 里声明了 `<depend>roboparty_imu</depend>`，但实际的
IMU 包名是 **`damiao_imu`**（`roboparty_imu` 已不存在，是历史命名残留）。

- 影响：`rosdep install --from-paths src` 会因找不到 `roboparty_imu` 而**报错**；
- 不影响：上面 §3 的 `colcon build --packages-select` 直接构建（CMake 里用的是
  `find_package(damiao_imu)`，是正确的）。

建议把该行改成 `<depend>damiao_imu</depend>`。

---

## 6. 常见问题排查

| 现象 | 原因 | 解决 |
|------|------|------|
| `The message type '...' is invalid` | 当前终端没 source 工作区 | `source /opt/ros/humble/setup.bash && source ~/Dog_deploy/install/setup.bash` |
| 链接报 `x86-64` 相关错误 | 用到了 x64 的 onnxruntime | 删 `src/inference/thirdparty/onnxruntime` 后重新 build |
| `rosdep` 报找不到 `roboparty_imu` | package.xml 包名残留 | 改为 `<depend>damiao_imu</depend>` |
| 串口 `Permission denied` | 没加 dialout 组 | `sudo usermod -a -G dialout $USER` 重新登录 |
| `operation not permitted` (mlockall/SCHED_FIFO) | 没 root | 用 `sudo -E` 启动 |
| IMU 打不开 | 设备路径不对 | `ls /dev/ttyACM*` 确认后改 `robot.yaml` |
