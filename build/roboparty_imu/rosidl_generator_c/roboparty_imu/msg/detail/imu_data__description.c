// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from roboparty_imu:msg/IMUData.idl
// generated code does not contain a copyright notice

#include "roboparty_imu/msg/detail/imu_data__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_roboparty_imu
const rosidl_type_hash_t *
roboparty_imu__msg__IMUData__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x30, 0x4b, 0xff, 0xdd, 0x60, 0xf5, 0xf3, 0x98,
      0x45, 0x7a, 0x6a, 0x4f, 0x4e, 0x0e, 0x1d, 0x7a,
      0x33, 0x2b, 0xc1, 0xa9, 0xa7, 0x86, 0x69, 0xc9,
      0x2b, 0x80, 0xab, 0xf8, 0x1f, 0x7c, 0x98, 0xdb,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char roboparty_imu__msg__IMUData__TYPE_NAME[] = "roboparty_imu/msg/IMUData";

// Define type names, field names, and default values
static char roboparty_imu__msg__IMUData__FIELD_NAME__device_id[] = "device_id";
static char roboparty_imu__msg__IMUData__FIELD_NAME__accel_x[] = "accel_x";
static char roboparty_imu__msg__IMUData__FIELD_NAME__accel_y[] = "accel_y";
static char roboparty_imu__msg__IMUData__FIELD_NAME__accel_z[] = "accel_z";
static char roboparty_imu__msg__IMUData__FIELD_NAME__gyro_x[] = "gyro_x";
static char roboparty_imu__msg__IMUData__FIELD_NAME__gyro_y[] = "gyro_y";
static char roboparty_imu__msg__IMUData__FIELD_NAME__gyro_z[] = "gyro_z";
static char roboparty_imu__msg__IMUData__FIELD_NAME__roll[] = "roll";
static char roboparty_imu__msg__IMUData__FIELD_NAME__pitch[] = "pitch";
static char roboparty_imu__msg__IMUData__FIELD_NAME__yaw[] = "yaw";
static char roboparty_imu__msg__IMUData__FIELD_NAME__q_w[] = "q_w";
static char roboparty_imu__msg__IMUData__FIELD_NAME__q_x[] = "q_x";
static char roboparty_imu__msg__IMUData__FIELD_NAME__q_y[] = "q_y";
static char roboparty_imu__msg__IMUData__FIELD_NAME__q_z[] = "q_z";

static rosidl_runtime_c__type_description__Field roboparty_imu__msg__IMUData__FIELDS[] = {
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__device_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__accel_x, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__accel_y, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__accel_z, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__gyro_x, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__gyro_y, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__gyro_z, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__roll, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__pitch, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__yaw, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__q_w, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__q_x, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__q_y, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {roboparty_imu__msg__IMUData__FIELD_NAME__q_z, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
roboparty_imu__msg__IMUData__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {roboparty_imu__msg__IMUData__TYPE_NAME, 25, 25},
      {roboparty_imu__msg__IMUData__FIELDS, 14, 14},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 device_id\n"
  "float32 accel_x\n"
  "float32 accel_y\n"
  "float32 accel_z\n"
  "float32 gyro_x\n"
  "float32 gyro_y\n"
  "float32 gyro_z\n"
  "float32 roll\n"
  "float32 pitch\n"
  "float32 yaw\n"
  "float32 q_w\n"
  "float32 q_x\n"
  "float32 q_y\n"
  "float32 q_z";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
roboparty_imu__msg__IMUData__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {roboparty_imu__msg__IMUData__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 196, 196},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
roboparty_imu__msg__IMUData__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *roboparty_imu__msg__IMUData__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
