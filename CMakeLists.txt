cmake_minimum_required(VERSION 3.15)
project(ActAn VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

file(GLOB SOURCES "main/src/*.cpp")

add_executable(actan ${SOURCES})

target_include_directories(actan PRIVATE main/include)

# --- Installation ---
install(TARGETS actan 
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
