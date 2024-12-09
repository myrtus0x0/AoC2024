#!/bin/bash

cd build
echo "running cmake..."
cmake .. 

echo "running make..."
make

echo "done"
