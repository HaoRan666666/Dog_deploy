// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from imu_ros2:msg/IMUData.idl
// generated code does not contain a copyright notice
#include "imu_ros2/msg/detail/imu_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
imu_ros2__msg__IMUData__init(imu_ros2__msg__IMUData * msg)
{
  if (!msg) {
    return false;
  }
  // device_id
  // accel_x
  // accel_y
  // accel_z
  // gyro_x
  // gyro_y
  // gyro_z
  // roll
  // pitch
  // yaw
  // q_w
  // q_x
  // q_y
  // q_z
  return true;
}

void
imu_ros2__msg__IMUData__fini(imu_ros2__msg__IMUData * msg)
{
  if (!msg) {
    return;
  }
  // device_id
  // accel_x
  // accel_y
  // accel_z
  // gyro_x
  // gyro_y
  // gyro_z
  // roll
  // pitch
  // yaw
  // q_w
  // q_x
  // q_y
  // q_z
}

bool
imu_ros2__msg__IMUData__are_equal(const imu_ros2__msg__IMUData * lhs, const imu_ros2__msg__IMUData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // device_id
  if (lhs->device_id != rhs->device_id) {
    return false;
  }
  // accel_x
  if (lhs->accel_x != rhs->accel_x) {
    return false;
  }
  // accel_y
  if (lhs->accel_y != rhs->accel_y) {
    return false;
  }
  // accel_z
  if (lhs->accel_z != rhs->accel_z) {
    return false;
  }
  // gyro_x
  if (lhs->gyro_x != rhs->gyro_x) {
    return false;
  }
  // gyro_y
  if (lhs->gyro_y != rhs->gyro_y) {
    return false;
  }
  // gyro_z
  if (lhs->gyro_z != rhs->gyro_z) {
    return false;
  }
  // roll
  if (lhs->roll != rhs->roll) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // q_w
  if (lhs->q_w != rhs->q_w) {
    return false;
  }
  // q_x
  if (lhs->q_x != rhs->q_x) {
    return false;
  }
  // q_y
  if (lhs->q_y != rhs->q_y) {
    return false;
  }
  // q_z
  if (lhs->q_z != rhs->q_z) {
    return false;
  }
  return true;
}

bool
imu_ros2__msg__IMUData__copy(
  const imu_ros2__msg__IMUData * input,
  imu_ros2__msg__IMUData * output)
{
  if (!input || !output) {
    return false;
  }
  // device_id
  output->device_id = input->device_id;
  // accel_x
  output->accel_x = input->accel_x;
  // accel_y
  output->accel_y = input->accel_y;
  // accel_z
  output->accel_z = input->accel_z;
  // gyro_x
  output->gyro_x = input->gyro_x;
  // gyro_y
  output->gyro_y = input->gyro_y;
  // gyro_z
  output->gyro_z = input->gyro_z;
  // roll
  output->roll = input->roll;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // q_w
  output->q_w = input->q_w;
  // q_x
  output->q_x = input->q_x;
  // q_y
  output->q_y = input->q_y;
  // q_z
  output->q_z = input->q_z;
  return true;
}

imu_ros2__msg__IMUData *
imu_ros2__msg__IMUData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_ros2__msg__IMUData * msg = (imu_ros2__msg__IMUData *)allocator.allocate(sizeof(imu_ros2__msg__IMUData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(imu_ros2__msg__IMUData));
  bool success = imu_ros2__msg__IMUData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
imu_ros2__msg__IMUData__destroy(imu_ros2__msg__IMUData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    imu_ros2__msg__IMUData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
imu_ros2__msg__IMUData__Sequence__init(imu_ros2__msg__IMUData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_ros2__msg__IMUData * data = NULL;

  if (size) {
    data = (imu_ros2__msg__IMUData *)allocator.zero_allocate(size, sizeof(imu_ros2__msg__IMUData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = imu_ros2__msg__IMUData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        imu_ros2__msg__IMUData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
imu_ros2__msg__IMUData__Sequence__fini(imu_ros2__msg__IMUData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      imu_ros2__msg__IMUData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

imu_ros2__msg__IMUData__Sequence *
imu_ros2__msg__IMUData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_ros2__msg__IMUData__Sequence * array = (imu_ros2__msg__IMUData__Sequence *)allocator.allocate(sizeof(imu_ros2__msg__IMUData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = imu_ros2__msg__IMUData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
imu_ros2__msg__IMUData__Sequence__destroy(imu_ros2__msg__IMUData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    imu_ros2__msg__IMUData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
imu_ros2__msg__IMUData__Sequence__are_equal(const imu_ros2__msg__IMUData__Sequence * lhs, const imu_ros2__msg__IMUData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!imu_ros2__msg__IMUData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
imu_ros2__msg__IMUData__Sequence__copy(
  const imu_ros2__msg__IMUData__Sequence * input,
  imu_ros2__msg__IMUData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(imu_ros2__msg__IMUData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    imu_ros2__msg__IMUData * data =
      (imu_ros2__msg__IMUData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!imu_ros2__msg__IMUData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          imu_ros2__msg__IMUData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!imu_ros2__msg__IMUData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
