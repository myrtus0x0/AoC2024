cmake_minimum_required(VERSION 3.10)
project(day03)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day03 main.cpp solution.cpp)

# Tests
add_executable(day03_test test/test.cpp solution.cpp)
target_include_directories(day03_test PRIVATE test)
