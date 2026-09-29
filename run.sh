#!/bin/bash

echo "Starting installation for ActAn..."

# 1. compile project
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

if [ $? -ne 0 ]; then
    echo "Error: Compilation failed. Make sure CMake and a C++ compiler are installed."
    exit 1
fi

# 2. find script path
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# 3. create alias depending on operating system
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    PROFILE_FILE="$HOME/.zshrc"
else
    # Linux
    PROFILE_FILE="$HOME/.bashrc"
fi

# check if alias exists, when not add it
if ! grep -q "alias actan=" "$PROFILE_FILE"; then
    echo "alias actan='$PROJECT_DIR/build/actan'" >> "$PROFILE_FILE"
    echo "Installation successful! Please restart your terminal or run: source $PROFILE_FILE"
    echo "You will then be able to use the 'actan' command from anywhere."
else
    echo "ActAn alias is already configured in $PROFILE_FILE."
fi

