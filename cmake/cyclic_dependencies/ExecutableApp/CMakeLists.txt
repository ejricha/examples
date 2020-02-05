# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(TestCycleMain LANGUAGES CXX)

add_executable(TestCycle test_cycle.cpp)

# TestCycle depends on A
target_link_libraries(TestCycle A)
