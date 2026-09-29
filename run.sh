#!/bin/bash

echo "Starting installation for ActAn..."

# compile project
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

if [ $? -ne 0 ]; then
    echo "Error: Compilation failed. Make sure CMake and a C++ compiler are installed."
    exit 1
fi

# find script path
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# make sure that python dependencies are installed
echo "Installing Python dependencies from requirements.txt..."
if command -v pip3 &> /dev/null; then
    pip3 install --upgrade pip --quiet
    pip3 install -r requirements.txt --quiet
elif command -v pip &> /dev/null; then
    pip install --upgrade pip --quiet
    pip install -r requirements.txt --quiet
else
    echo "Warning: pip was not found. Could not install Python dependencies automatically."
	echo "You will need to install 'numpy', 'matplotlib' and 'scipy' manually."
fi


# create alias depending on operating system
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
    echo "If you need help just enter 'actan --help' in the command line."
else
    echo "ActAn alias is already configured in $PROFILE_FILE."
fi

