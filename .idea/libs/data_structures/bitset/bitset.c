#include <stdio.h>
#include <assert.h>
#include "bitset.h"

bitset bitset_create(unsigned maxValue) {
    assert(maxValue < 32);
    return (bitset) {0, maxValue};
}

bitset bitset_create_from_array(const unsigned int a[], size_t size, unsigned maxValue) {
    assert(size < 32);
    bitset set = bitset_create(maxValue);
    for (size_t i = 0; i < size; i++)
        bitset_insert(&set, *(a + i));
    return set;
}

bool bitset_in(bitset set, unsigned value) {
    return set.values & (1 << value);
}

bool bitset_is_equal(bitset set1, bitset set2) {
    return set1.values == set2.values;
}

bool bitset_is_subset(bitset subset, bitset set) {
    return (set.values & subset.values) == subset.values;
}

void bitset_insert(bitset* set, unsigned value) {
    set -> values = (set -> values) | (1 << value);
}

void bitset_delete_element(bitset* set, unsigned value) {
    set -> values = (set -> values) & ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values | set2.values, set1.maxValue};
}

bitset bitset_intersection(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values};
}

bitset bitset_difference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & ~set2.values};
}

bitset bitset_symmetric_difference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values ^ set2.values};
}

bitset bitset_complement(bitset set) {
    uint32_t universum = (1 << (set.maxValue + 1)) - 1;
    return (bitset) {set.values ^ universum, set.maxValue};
}

void bitset_print(bitset set) {
    printf ("{") ;
    int is_empty = 1;
    for (int i = 0; i <= set.maxValue; i++) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            is_empty = 0;
        }
    }

    if (is_empty)
        printf("}\n");
    else
        printf("\b\b}\n");
}