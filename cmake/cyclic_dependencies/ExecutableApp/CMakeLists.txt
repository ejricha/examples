# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(TestCycleMain LANGUAGES CXX)

add_executable(test_cycle test_cycle.cpp)
target_link_libraries(test_cycle a)
