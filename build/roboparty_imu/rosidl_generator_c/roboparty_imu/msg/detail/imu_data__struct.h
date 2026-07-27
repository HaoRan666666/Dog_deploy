// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "roboparty_imu/msg/imu_data.h"


#ifndef ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__STRUCT_H_
#define ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/IMUData in the package roboparty_imu.
typedef struct roboparty_imu__msg__IMUData
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
} roboparty_imu__msg__IMUData;

// Struct for a sequence of roboparty_imu__msg__IMUData.
typedef struct roboparty_imu__msg__IMUData__Sequence
{
  roboparty_imu__msg__IMUData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} roboparty_imu__msg__IMUData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__STRUCT_H_
