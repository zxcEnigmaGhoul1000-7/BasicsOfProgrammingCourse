add_library(data_structures
        bitset/bitset.c
        ordered_set/ordered_set.c
        unordered_set/unordered_set.c
        vectorVoid/vectorVoid.c
        vector/vector.c
        matrix/matrix.c
)

target_link_libraries(data_structures algorithms)