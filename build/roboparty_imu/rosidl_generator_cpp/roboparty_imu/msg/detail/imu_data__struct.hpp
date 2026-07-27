// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "roboparty_imu/msg/imu_data.hpp"


#ifndef ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__STRUCT_HPP_
#define ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__roboparty_imu__msg__IMUData __attribute__((deprecated))
#else
# define DEPRECATED__roboparty_imu__msg__IMUData __declspec(deprecated)
#endif

namespace roboparty_imu
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct IMUData_
{
  using Type = IMUData_<ContainerAllocator>;

  explicit IMUData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device_id = 0;
      this->accel_x = 0.0f;
      this->accel_y = 0.0f;
      this->accel_z = 0.0f;
      this->gyro_x = 0.0f;
      this->gyro_y = 0.0f;
      this->gyro_z = 0.0f;
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw = 0.0f;
      this->q_w = 0.0f;
      this->q_x = 0.0f;
      this->q_y = 0.0f;
      this->q_z = 0.0f;
    }
  }

  explicit IMUData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device_id = 0;
      this->accel_x = 0.0f;
      this->accel_y = 0.0f;
      this->accel_z = 0.0f;
      this->gyro_x = 0.0f;
      this->gyro_y = 0.0f;
      this->gyro_z = 0.0f;
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw = 0.0f;
      this->q_w = 0.0f;
      this->q_x = 0.0f;
      this->q_y = 0.0f;
      this->q_z = 0.0f;
    }
  }

  // field types and members
  using _device_id_type =
    uint8_t;
  _device_id_type device_id;
  using _accel_x_type =
    float;
  _accel_x_type accel_x;
  using _accel_y_type =
    float;
  _accel_y_type accel_y;
  using _accel_z_type =
    float;
  _accel_z_type accel_z;
  using _gyro_x_type =
    float;
  _gyro_x_type gyro_x;
  using _gyro_y_type =
    float;
  _gyro_y_type gyro_y;
  using _gyro_z_type =
    float;
  _gyro_z_type gyro_z;
  using _roll_type =
    float;
  _roll_type roll;
  using _pitch_type =
    float;
  _pitch_type pitch;
  using _yaw_type =
    float;
  _yaw_type yaw;
  using _q_w_type =
    float;
  _q_w_type q_w;
  using _q_x_type =
    float;
  _q_x_type q_x;
  using _q_y_type =
    float;
  _q_y_type q_y;
  using _q_z_type =
    float;
  _q_z_type q_z;

  // setters for named parameter idiom
  Type & set__device_id(
    const uint8_t & _arg)
  {
    this->device_id = _arg;
    return *this;
  }
  Type & set__accel_x(
    const float & _arg)
  {
    this->accel_x = _arg;
    return *this;
  }
  Type & set__accel_y(
    const float & _arg)
  {
    this->accel_y = _arg;
    return *this;
  }
  Type & set__accel_z(
    const float & _arg)
  {
    this->accel_z = _arg;
    return *this;
  }
  Type & set__gyro_x(
    const float & _arg)
  {
    this->gyro_x = _arg;
    return *this;
  }
  Type & set__gyro_y(
    const float & _arg)
  {
    this->gyro_y = _arg;
    return *this;
  }
  Type & set__gyro_z(
    const float & _arg)
  {
    this->gyro_z = _arg;
    return *this;
  }
  Type & set__roll(
    const float & _arg)
  {
    this->roll = _arg;
    return *this;
  }
  Type & set__pitch(
    const float & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__q_w(
    const float & _arg)
  {
    this->q_w = _arg;
    return *this;
  }
  Type & set__q_x(
    const float & _arg)
  {
    this->q_x = _arg;
    return *this;
  }
  Type & set__q_y(
    const float & _arg)
  {
    this->q_y = _arg;
    return *this;
  }
  Type & set__q_z(
    const float & _arg)
  {
    this->q_z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    roboparty_imu::msg::IMUData_<ContainerAllocator> *;
  using ConstRawPtr =
    const roboparty_imu::msg::IMUData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      roboparty_imu::msg::IMUData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      roboparty_imu::msg::IMUData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__roboparty_imu__msg__IMUData
    std::shared_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__roboparty_imu__msg__IMUData
    std::shared_ptr<roboparty_imu::msg::IMUData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IMUData_ & other) const
  {
    if (this->device_id != other.device_id) {
      return false;
    }
    if (this->accel_x != other.accel_x) {
      return false;
    }
    if (this->accel_y != other.accel_y) {
      return false;
    }
    if (this->accel_z != other.accel_z) {
      return false;
    }
    if (this->gyro_x != other.gyro_x) {
      return false;
    }
    if (this->gyro_y != other.gyro_y) {
      return false;
    }
    if (this->gyro_z != other.gyro_z) {
      return false;
    }
    if (this->roll != other.roll) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->q_w != other.q_w) {
      return false;
    }
    if (this->q_x != other.q_x) {
      return false;
    }
    if (this->q_y != other.q_y) {
      return false;
    }
    if (this->q_z != other.q_z) {
      return false;
    }
    return true;
  }
  bool operator!=(const IMUData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IMUData_

// alias to use template instance with default allocator
using IMUData =
  roboparty_imu::msg::IMUData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace roboparty_imu

#endif  // ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__STRUCT_HPP_
