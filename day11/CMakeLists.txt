cmake_minimum_required(VERSION 3.10)
project(day11)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

# Main executable
add_executable(day11 main.cpp solution.cpp)

# Tests
add_executable(day11_test test/test.cpp solution.cpp)
target_include_directories(day11_test PRIVATE test)
