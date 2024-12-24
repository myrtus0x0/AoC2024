cmake_minimum_required(VERSION 3.10)
project(day10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day10 main.cpp solution.cpp)

# Tests
add_executable(day10_test test/test.cpp solution.cpp)
target_include_directories(day10_test PRIVATE test)
