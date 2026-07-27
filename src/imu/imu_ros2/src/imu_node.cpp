/**
 * DM-IMU ROS2 节点
 */

#include "imu_reader.h"

#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <roboparty_imu/msg/imu_data.hpp>

class IMUNode : public rclcpp::Node {
public:
    IMUNode(const std::string &device, int baud)
        : Node("imu_node")
    {
        pub_ = this->create_publisher<roboparty_imu::msg::IMUData>("/imu", 10);

        if (!reader_.open(device, baud)) {
            RCLCPP_ERROR(this->get_logger(), "无法打开 %s（节点保持运行但不发布）", device.c_str());
            return;
        }
        reader_.configure();
        RCLCPP_INFO(this->get_logger(), "IMU 已连接: %s @ %d", device.c_str(), baud);

        reader_.setCallback([this](const IMUData &d) {
            if (d.updated & 1) { latest_.accel = d.accel; latest_.updated |= 1; }
            if (d.updated & 2) { latest_.gyro  = d.gyro;  latest_.updated |= 2; }
            if (d.updated & 4) { latest_.euler = d.euler; latest_.updated |= 4; }
            if (d.updated & 8) { latest_.quat  = d.quat;  latest_.updated |= 8; }
        });

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1),
            std::bind(&IMUNode::tick, this));
    }

private:
    IMUReader reader_;
    rclcpp::Publisher<roboparty_imu::msg::IMUData>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    IMUData latest_{};

    void tick() {
        reader_.update();
        if (latest_.updated != 0x0F) return;
        latest_.updated = 0;

        auto msg = roboparty_imu::msg::IMUData();
        msg.device_id = latest_.device_id;
        msg.accel_x = latest_.accel.x;
        msg.accel_y = latest_.accel.y;
        msg.accel_z = latest_.accel.z;
        msg.gyro_x = latest_.gyro.x;
        msg.gyro_y = latest_.gyro.y;
        msg.gyro_z = latest_.gyro.z;
        msg.roll = latest_.euler.x;
        msg.pitch = latest_.euler.y;
        msg.yaw = latest_.euler.z;
        msg.q_w = latest_.quat.w;
        msg.q_x = latest_.quat.x;
        msg.q_y = latest_.quat.y;
        msg.q_z = latest_.quat.z;

        pub_->publish(msg);
    }
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <device> [baud]\n", argv[0]);
        return 1;
    }
    rclcpp::spin(std::make_shared<IMUNode>(argv[1], argc > 2 ? atoi(argv[2]) : 921600));
    rclcpp::shutdown();
    return 0;
}
