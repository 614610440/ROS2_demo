cmake_minimum_required(VERSION 3.5)
project(wxx_publisher)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(wxx_publisher publisher.cpp)
ament_target_dependencies(wxx_publisher rclcpp std_msgs)

install(TARGETS
    wxx_publisher
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()