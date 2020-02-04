# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(LibraryA LANGUAGES CXX)

add_library(a a.cpp)
target_link_libraries(a b) # a depends on b
