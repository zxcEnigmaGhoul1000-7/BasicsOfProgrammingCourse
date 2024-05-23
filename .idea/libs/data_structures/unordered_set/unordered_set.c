#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include "../../algorithms/array/array.h"
#include "unordered_set.h"
static int compare_ints(const void* a, const void* b) {
    return *(int* ) a - *(int* ) b;
}
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}
void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set -> size < set -> capacity);
}
size_t unordered_array_set_in(unordered_array_set set, int value) {
    return linearSearch_(set.data, set.size, value);
}
void unordered_array_set_insert(unordered_array_set* set, int value) {
    if (unordered_array_set_in(*set, value) == set -> size) {
        unordered_array_set_isAbleAppend(set);
        append_(set -> data, &set -> size, value);
    }
}
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size)
        return 0;
    qsort(set1.data, set1.size, sizeof(int), compare_ints);
    qsort(set2.data, set2.size, sizeof(int), compare_ints);
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}
static void unordered_array_set_shrinkToFit(unordered_array_set* a) {
    if (a -> size != a -> capacity) {
        a -> data = (int*)realloc(a -> data, sizeof(int) * a -> size);
        a -> capacity = a -> size;
    }
}
unordered_array_set unordered_array_set_create_from_array(const int* a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);
    unordered_array_set_shrinkToFit(&set);
    return set;
}
bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    for (size_t i = 0; i < subset.size; i++) {
        bool found = false;
        for (size_t j = 0; j < set.size; j++)
            if (subset.data[i] == set.data[j]) {
                found = true;
                break;
            }
        if (!found)
            return false;
    }
    return true;
}
void unordered_array_set_deleteElement(unordered_array_set* set, int value){
    size_t index_value = unordered_array_set_in(*set, value);
    if (index_value < set -> size) {
        set->data[index_value] = set->data[set->size - 1];
        (set->size)--;
    }
}
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size + set2.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < set1.size; i++) {
        set.data[i] = set1.data[i];
        set.size++;
    }
    for (size_t i = 0; i < set2.size; i++)
        unordered_array_set_insert(&set, set2.data[i]);
    unordered_array_set_shrinkToFit(&set);
    return set;
}
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size < set2.size ? set1.size : set2.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size)
            unordered_array_set_insert(&set, set1.data[i]);
    return set;
}
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(set2, set1.data[i]) == set2.size)
            unordered_array_set_insert(&set, set1.data[i]);
    return set;
}
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universum_set) {
    size_t new_capacity = universum_set.size;
    unordered_array_set new_set = unordered_array_set_create(new_capacity);
    for (size_t i = 0; i < universum_set.size; i++)
        if (unordered_array_set_in(set, universum_set.data[i]) == set.size)
            unordered_array_set_insert(&new_set, universum_set.data[i]);
    assert(unordered_array_set_isSubset(new_set, universum_set));
    return new_set;
}
void unordered_array_set_delete(unordered_array_set set) {
    free(&set);
}
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set universum = unordered_array_set_union(set1, set2);
    unordered_array_set intersection = unordered_array_set_intersection(set1,
                                                                        set2);
    unordered_array_set symmetric = unordered_array_set_complement(intersection, universum);
    unordered_array_set_delete(intersection);
    unordered_array_set_delete(universum);
    return symmetric;
}
void unordered_array_set_print ( unordered_array_set set ) {
    printf("{");
    int is_empty = 1;
    for (size_t i = 0; i < set.size; i++) {
        printf("%d, ", *(set.data + i));
        is_empty = 0;
    }
    if (is_empty)
        printf("}\n");
    else
        printf("\b\b}\n");
}
