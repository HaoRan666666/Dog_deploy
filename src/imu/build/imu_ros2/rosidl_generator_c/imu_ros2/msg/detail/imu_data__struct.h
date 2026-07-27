// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from imu_ros2:msg/IMUData.idl
// generated code does not contain a copyright notice

#ifndef IMU_ROS2__MSG__DETAIL__IMU_DATA__STRUCT_H_
#define IMU_ROS2__MSG__DETAIL__IMU_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/IMUData in the package imu_ros2.
typedef struct imu_ros2__msg__IMUData
{
  uint8_t device_id;
  float accel_x;
  float accel_y;
  float accel_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float roll;
  float pitch;
  float yaw;
  float q_w;
  float q_x;
  float q_y;
  float q_z;
} imu_ros2__msg__IMUData;

// Struct for a sequence of imu_ros2__msg__IMUData.
typedef struct imu_ros2__msg__IMUData__Sequence
{
  imu_ros2__msg__IMUData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} imu_ros2__msg__IMUData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IMU_ROS2__MSG__DETAIL__IMU_DATA__STRUCT_H_
