// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice
#ifndef ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "roboparty_imu/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "roboparty_imu/msg/detail/imu_data__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
bool cdr_serialize_roboparty_imu__msg__IMUData(
  const roboparty_imu__msg__IMUData * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
bool cdr_deserialize_roboparty_imu__msg__IMUData(
  eprosima::fastcdr::Cdr &,
  roboparty_imu__msg__IMUData * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
size_t get_serialized_size_roboparty_imu__msg__IMUData(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
size_t max_serialized_size_roboparty_imu__msg__IMUData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
bool cdr_serialize_key_roboparty_imu__msg__IMUData(
  const roboparty_imu__msg__IMUData * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
size_t get_serialized_size_key_roboparty_imu__msg__IMUData(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
size_t max_serialized_size_key_roboparty_imu__msg__IMUData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_roboparty_imu
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, roboparty_imu, msg, IMUData)();

#ifdef __cplusplus
}
#endif

#endif  // ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
