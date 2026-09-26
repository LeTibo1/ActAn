cmake_minimum_required(VERSION 3.15)
project(ActAn VERSION 1.0 LANGUAGES CXX)

# C++ Standard festlegen (z. B. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dem Compiler sagen, wo er nach Header-Dateien (.h) suchen soll
include_directories(include)

# Alle Quelldateien (.cpp) im src-Ordner automatisch sammeln
file(GLOB SOURCES "src/*.cpp")

# Die ausführbare Datei (Executable) erstellen
add_executable(actan ${SOURCES})
