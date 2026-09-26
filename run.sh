#!/bin/bash
set -e

cur_dir=$PWD
cd "$(dirname "$0")"

mkdir -p build
cd build

cmake ..
cmake --build .

# NEU: Kopiert das fertige Programm in das Systemverzeichnis.
# Da /usr/local/bin geschützt ist, wird nach deinem Mac-Passwort gefragt.
#sudo cmake --install .

cd ..
#echo "Installation successful!"

build/actan "$cur_dir"
