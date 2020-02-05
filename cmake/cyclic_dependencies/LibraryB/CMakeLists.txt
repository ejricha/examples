# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(LibraryB LANGUAGES CXX)

add_library(b b.cpp)
target_link_libraries(b c) # b depends on c
