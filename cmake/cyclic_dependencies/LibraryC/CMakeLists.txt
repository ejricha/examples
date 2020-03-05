add_library(C c.cpp)

# C depends on A
target_link_libraries(C PUBLIC A)
