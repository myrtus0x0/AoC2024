cmake_minimum_required(VERSION 3.10)
project(day05)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day05 main.cpp solution.cpp)

# Tests
add_executable(day05_test test/test.cpp solution.cpp)
target_include_directories(day05_test PRIVATE test)
