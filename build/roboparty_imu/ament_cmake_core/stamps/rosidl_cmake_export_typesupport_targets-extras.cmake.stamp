# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_generator_c:roboparty_imu__rosidl_generator_c;__rosidl_typesupport_fastrtps_c:roboparty_imu__rosidl_typesupport_fastrtps_c;__rosidl_generator_cpp:roboparty_imu__rosidl_generator_cpp;__rosidl_typesupport_fastrtps_cpp:roboparty_imu__rosidl_typesupport_fastrtps_cpp;__rosidl_typesupport_introspection_c:roboparty_imu__rosidl_typesupport_introspection_c;__rosidl_typesupport_c:roboparty_imu__rosidl_typesupport_c;__rosidl_typesupport_introspection_cpp:roboparty_imu__rosidl_typesupport_introspection_cpp;__rosidl_typesupport_cpp:roboparty_imu__rosidl_typesupport_cpp;:roboparty_imu__rosidl_generator_py")

# populate roboparty_imu_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "roboparty_imu::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'roboparty_imu' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND roboparty_imu_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()
