cmake_minimum_required(VERSION 3.10)
project(day06)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day06 main.cpp solution.cpp)

# Tests
add_executable(day06_test test/test.cpp solution.cpp)
target_include_directories(day06_test PRIVATE test)
