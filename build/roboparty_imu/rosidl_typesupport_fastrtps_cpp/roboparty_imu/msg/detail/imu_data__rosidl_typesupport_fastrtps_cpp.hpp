// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice

#ifndef ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "roboparty_imu/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "roboparty_imu/msg/detail/imu_data__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace roboparty_imu
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
cdr_serialize(
  const roboparty_imu::msg::IMUData & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  roboparty_imu::msg::IMUData & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
get_serialized_size(
  const roboparty_imu::msg::IMUData & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
max_serialized_size_IMUData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
cdr_serialize_key(
  const roboparty_imu::msg::IMUData & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
get_serialized_size_key(
  const roboparty_imu::msg::IMUData & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
max_serialized_size_key_IMUData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace roboparty_imu

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_roboparty_imu
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, roboparty_imu, msg, IMUData)();

#ifdef __cplusplus
}
#endif

#endif  // ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
