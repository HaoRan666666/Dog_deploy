// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "roboparty_imu/msg/imu_data.hpp"


#ifndef ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__TRAITS_HPP_
#define ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "roboparty_imu/msg/detail/imu_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace roboparty_imu
{

namespace msg
{

inline void to_flow_style_yaml(
  const IMUData & msg,
  std::ostream & out)
{
  out << "{";
  // member: device_id
  {
    out << "device_id: ";
    rosidl_generator_traits::value_to_yaml(msg.device_id, out);
    out << ", ";
  }

  // member: accel_x
  {
    out << "accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_x, out);
    out << ", ";
  }

  // member: accel_y
  {
    out << "accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_y, out);
    out << ", ";
  }

  // member: accel_z
  {
    out << "accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_z, out);
    out << ", ";
  }

  // member: gyro_x
  {
    out << "gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_x, out);
    out << ", ";
  }

  // member: gyro_y
  {
    out << "gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_y, out);
    out << ", ";
  }

  // member: gyro_z
  {
    out << "gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_z, out);
    out << ", ";
  }

  // member: roll
  {
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << ", ";
  }

  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: q_w
  {
    out << "q_w: ";
    rosidl_generator_traits::value_to_yaml(msg.q_w, out);
    out << ", ";
  }

  // member: q_x
  {
    out << "q_x: ";
    rosidl_generator_traits::value_to_yaml(msg.q_x, out);
    out << ", ";
  }

  // member: q_y
  {
    out << "q_y: ";
    rosidl_generator_traits::value_to_yaml(msg.q_y, out);
    out << ", ";
  }

  // member: q_z
  {
    out << "q_z: ";
    rosidl_generator_traits::value_to_yaml(msg.q_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IMUData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: device_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "device_id: ";
    rosidl_generator_traits::value_to_yaml(msg.device_id, out);
    out << "\n";
  }

  // member: accel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_x, out);
    out << "\n";
  }

  // member: accel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_y, out);
    out << "\n";
  }

  // member: accel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_z, out);
    out << "\n";
  }

  // member: gyro_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_x, out);
    out << "\n";
  }

  // member: gyro_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_y, out);
    out << "\n";
  }

  // member: gyro_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_z, out);
    out << "\n";
  }

  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << "\n";
  }

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: q_w
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_w: ";
    rosidl_generator_traits::value_to_yaml(msg.q_w, out);
    out << "\n";
  }

  // member: q_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_x: ";
    rosidl_generator_traits::value_to_yaml(msg.q_x, out);
    out << "\n";
  }

  // member: q_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_y: ";
    rosidl_generator_traits::value_to_yaml(msg.q_y, out);
    out << "\n";
  }

  // member: q_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_z: ";
    rosidl_generator_traits::value_to_yaml(msg.q_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IMUData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace roboparty_imu

namespace rosidl_generator_traits
{

[[deprecated("use roboparty_imu::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const roboparty_imu::msg::IMUData & msg,
  std::ostream & out, size_t indentation = 0)
{
  roboparty_imu::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use roboparty_imu::msg::to_yaml() instead")]]
inline std::string to_yaml(const roboparty_imu::msg::IMUData & msg)
{
  return roboparty_imu::msg::to_yaml(msg);
}

template<>
inline const char * data_type<roboparty_imu::msg::IMUData>()
{
  return "roboparty_imu::msg::IMUData";
}

template<>
inline const char * name<roboparty_imu::msg::IMUData>()
{
  return "roboparty_imu/msg/IMUData";
}

template<>
struct has_fixed_size<roboparty_imu::msg::IMUData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<roboparty_imu::msg::IMUData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<roboparty_imu::msg::IMUData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOPARTY_IMU__MSG__DETAIL__IMU_DATA__TRAITS_HPP_
