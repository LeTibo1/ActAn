#!/bin/bash

set -e
mkdir -p build
cd build

# compile
cmake ..
cmake --build .

cd ..

# run program
./build/actan
