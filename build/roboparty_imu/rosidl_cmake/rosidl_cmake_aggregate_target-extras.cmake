# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target roboparty_imu::roboparty_imu
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${roboparty_imu_TARGETS}.
if(roboparty_imu_TARGETS AND NOT TARGET roboparty_imu::roboparty_imu)
  add_library(roboparty_imu::roboparty_imu INTERFACE IMPORTED)
  set_target_properties(roboparty_imu::roboparty_imu PROPERTIES
    INTERFACE_LINK_LIBRARIES "${roboparty_imu_TARGETS}")
endif()
