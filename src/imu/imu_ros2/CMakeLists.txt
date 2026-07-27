cmake_minimum_required(VERSION 3.14)
project(roboparty_imu)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

# 自定义消息
rosidl_generate_interfaces(${PROJECT_NAME}
    msg/IMUData.msg
)

# IMU 串口库
add_library(imu_reader_lib STATIC
    src/crc16.cpp
    src/imu_parser.cpp
    src/imu_reader.cpp
    src/serial_port.cpp
)
target_include_directories(imu_reader_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imu_ros2>
    $<INSTALL_INTERFACE:include/imu_ros2>
)

# IMU 节点
add_executable(imu_node src/imu_node.cpp)
target_include_directories(imu_node PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imu_ros2>
)
ament_target_dependencies(imu_node rclcpp)
rosidl_target_interfaces(imu_node ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(imu_node imu_reader_lib)

# IMU 驱动抽象层 (兼容旧 roboparty_imu 接口)
add_library(imu_driver STATIC
    src/imu_driver.cpp
)
target_include_directories(imu_driver PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imu_ros2>
    $<INSTALL_INTERFACE:include/imu_ros2>
)
target_link_libraries(imu_driver PUBLIC imu_reader_lib)

install(TARGETS imu_node DESTINATION lib/${PROJECT_NAME})

install(TARGETS imu_reader_lib imu_driver
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

ament_export_include_directories(include)
ament_export_libraries(imu_reader_lib imu_driver)

ament_package()
