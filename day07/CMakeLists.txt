cmake_minimum_required(VERSION 3.10)
project(day07)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day07 main.cpp solution.cpp)

# Tests
add_executable(day07_test test/test.cpp solution.cpp)
target_include_directories(day07_test PRIVATE test)
