cmake_minimum_required(VERSION 3.26)
project(untitled6 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab main.c
        libs/algorithms/array/array.c
        libs/algorithms/array/array.h
        libs/algorithms/algorithm.c
        libs/algorithms/algorithm.h
        libs/data_structures/bitset/bitset.c
        libs/data_structures/bitset/bitset.h
        libs/data_structures/unordered_set/unordered_set.c
        libs/data_structures/unordered_set/unordered_set.h
        libs/data_structures/ordered_set/ordered_set.c
        libs/data_structures/ordered_set/ordered_set.h
        libs/data_structures/ordered_set/ordered_set.c
        libs/data_structures/vector/vector.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vectorVoid/vectorVoid.c
        libs/data_structures/vectorVoid/vectorVoid.h)
add_subdirectory(libs)
target_link_libraries(lab data_structures)
target_link_libraries(lab algorithms)