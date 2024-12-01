#!/bin/bash

if [ $# -ne 1 ]; then
    echo "usage: $0 <day_number>"
    exit 1
fi

day=$1
if ! [[ "$day" =~ ^[1-9][0-9]?$ ]] || [ "$day" -gt 25 ]; then
    echo "error: day must be between 1 and 25"
    exit 1
fi

padded_day=$(printf "%02d" $day)

day_dir="day$padded_day"
mkdir -p $day_dir
mkdir -p $day_dir/test
mkdir -p $day_dir/build

touch $day_dir/input.txt
touch $day_dir/example.txt

cp template/solution.cpp $day_dir
cp template/main.cpp $day_dir
cp template/test.cpp $day_dir/test
cp template/build.sh $day_dir

# copy headers 
cp template/*.hpp $day_dir
cp template/doctest.h $day_dir/test

# make dynamic cmake deps
cat > $day_dir/CMakeLists.txt << EOL
cmake_minimum_required(VERSION 3.10)
project(day$padded_day)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(day$padded_day main.cpp solution.cpp)

# Tests
add_executable(day${padded_day}_test test/test.cpp solution.cpp)
target_include_directories(day${padded_day}_test PRIVATE test)
EOL

echo "created day$padded_day directory with files"
