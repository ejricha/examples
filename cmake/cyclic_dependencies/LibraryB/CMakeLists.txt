add_library(B b.cpp)

# B depends on C
target_link_libraries(B C)
