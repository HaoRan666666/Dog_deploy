// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "roboparty_imu/msg/imu_data.hpp"


#ifndef ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__BUILDER_HPP_
#define ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "roboparty_imu/msg/detail/imu_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace roboparty_imu
{

namespace msg
{

namespace builder
{

class Init_IMUData_q_z
{
public:
  explicit Init_IMUData_q_z(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  ::roboparty_imu::msg::IMUData q_z(::roboparty_imu::msg::IMUData::_q_z_type arg)
  {
    msg_.q_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_q_y
{
public:
  explicit Init_IMUData_q_y(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_q_z q_y(::roboparty_imu::msg::IMUData::_q_y_type arg)
  {
    msg_.q_y = std::move(arg);
    return Init_IMUData_q_z(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_q_x
{
public:
  explicit Init_IMUData_q_x(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_q_y q_x(::roboparty_imu::msg::IMUData::_q_x_type arg)
  {
    msg_.q_x = std::move(arg);
    return Init_IMUData_q_y(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_q_w
{
public:
  explicit Init_IMUData_q_w(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_q_x q_w(::roboparty_imu::msg::IMUData::_q_w_type arg)
  {
    msg_.q_w = std::move(arg);
    return Init_IMUData_q_x(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_yaw
{
public:
  explicit Init_IMUData_yaw(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_q_w yaw(::roboparty_imu::msg::IMUData::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_IMUData_q_w(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_pitch
{
public:
  explicit Init_IMUData_pitch(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_yaw pitch(::roboparty_imu::msg::IMUData::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_IMUData_yaw(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_roll
{
public:
  explicit Init_IMUData_roll(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_pitch roll(::roboparty_imu::msg::IMUData::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_IMUData_pitch(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_gyro_z
{
public:
  explicit Init_IMUData_gyro_z(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_roll gyro_z(::roboparty_imu::msg::IMUData::_gyro_z_type arg)
  {
    msg_.gyro_z = std::move(arg);
    return Init_IMUData_roll(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_gyro_y
{
public:
  explicit Init_IMUData_gyro_y(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_gyro_z gyro_y(::roboparty_imu::msg::IMUData::_gyro_y_type arg)
  {
    msg_.gyro_y = std::move(arg);
    return Init_IMUData_gyro_z(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_gyro_x
{
public:
  explicit Init_IMUData_gyro_x(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_gyro_y gyro_x(::roboparty_imu::msg::IMUData::_gyro_x_type arg)
  {
    msg_.gyro_x = std::move(arg);
    return Init_IMUData_gyro_y(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_accel_z
{
public:
  explicit Init_IMUData_accel_z(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_gyro_x accel_z(::roboparty_imu::msg::IMUData::_accel_z_type arg)
  {
    msg_.accel_z = std::move(arg);
    return Init_IMUData_gyro_x(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_accel_y
{
public:
  explicit Init_IMUData_accel_y(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_accel_z accel_y(::roboparty_imu::msg::IMUData::_accel_y_type arg)
  {
    msg_.accel_y = std::move(arg);
    return Init_IMUData_accel_z(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_accel_x
{
public:
  explicit Init_IMUData_accel_x(::roboparty_imu::msg::IMUData & msg)
  : msg_(msg)
  {}
  Init_IMUData_accel_y accel_x(::roboparty_imu::msg::IMUData::_accel_x_type arg)
  {
    msg_.accel_x = std::move(arg);
    return Init_IMUData_accel_y(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

class Init_IMUData_device_id
{
public:
  Init_IMUData_device_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IMUData_accel_x device_id(::roboparty_imu::msg::IMUData::_device_id_type arg)
  {
    msg_.device_id = std::move(arg);
    return Init_IMUData_accel_x(msg_);
  }

private:
  ::roboparty_imu::msg::IMUData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::roboparty_imu::msg::IMUData>()
{
  return roboparty_imu::msg::builder::Init_IMUData_device_id();
}

}  // namespace roboparty_imu

#endif  // ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__BUILDER_HPP_
