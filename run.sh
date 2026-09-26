#!/bin/bash

set -e
mkdir build
cd build

# compile
cmake ..
cmake --build .

cd ..

# run program
./build/ActAn
