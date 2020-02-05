# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(LibraryB LANGUAGES CXX)

add_library(B b.cpp)

# B depends on C
target_link_libraries(B C)
