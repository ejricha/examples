# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(LibraryC LANGUAGES CXX)

add_library(C c.cpp)

# C depends on A
target_link_libraries(C A)
