cmake_minimum_required(VERSION 3.15)
project(LinkTypes LANGUAGES CXX)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All applications will end in .bin
set(CMAKE_EXECUTABLE_SUFFIX .bin)

# Build the src/ directory
add_subdirectory(src)
