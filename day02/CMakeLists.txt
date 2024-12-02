cmake_minimum_required(VERSION 3.10)
project(day02)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day02 main.cpp solution.cpp)

# Tests
add_executable(day02_test test/test.cpp solution.cpp)
target_include_directories(day02_test PRIVATE test)
