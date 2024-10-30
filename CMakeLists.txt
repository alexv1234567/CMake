# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set project name
project(IMU6050Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add executable
add_executable(IMU6050_example main.cpp src/IMU6050.cpp)

# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

