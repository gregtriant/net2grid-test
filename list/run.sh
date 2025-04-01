#!/bin/bash

# Navigate to the build directory (create if it doesn't exist)
if [ ! -d "build" ]; then
  mkdir build
fi
cd build

# Run CMake
make clean
cmake -DDEBUG_MODE=OFF ..

# Run Make
make

# Run the executable (assuming it's named 'my_executable')
./my_executable

# Optionally, return to the project root directory
cd ..