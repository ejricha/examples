# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(LibraryC LANGUAGES CXX)

add_library(c c.cpp)
target_link_libraries(c a) # c depends on a
