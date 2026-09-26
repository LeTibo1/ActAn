cmake_minimum_required(VERSION 3.15)
project(ActAn VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# header files
include_directories(main/include)

# .cpp files
file(GLOB SOURCES "main/src/*.cpp")

# create executable
add_executable(actan ${SOURCES})
