add_library(A a.cpp)

# A depends on B
target_link_libraries(A B)
