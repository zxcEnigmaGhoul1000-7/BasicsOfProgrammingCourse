#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include "../../algorithms/array/array.h"
#include "../../data_structures/ordered_set/ordered_set.h"

static int compare_ints(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}
ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}
void ordered_array_set_is_able_append(ordered_array_set *set) {
    assert(set->size < set->capacity);
}
size_t ordered_array_set_in(ordered_array_set *set, int value) {
    return binarySearch_(set->data, set->size, value);
}
void ordered_array_set_insert(ordered_array_set *set, int value) {
    size_t index = ordered_array_set_in(set, value);
    if (index == set->size) {
        ordered_array_set_is_able_append(set);
        size_t i;
        for (i = set->size; (i > 0 && set->data[i - 1] > value); i--)
            set->data[i] = set->data[i - 1];
        set->data[i] = value;
        set->size++;
    }
}
bool ordered_array_set_is_equal(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size)
        return 0;
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}
void ordered_array_set_shrink_to_fit(ordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        ordered_array_set_insert(&set, *(a + i));
    ordered_array_set_shrink_to_fit(&set);
    return set;
}
bool ordered_array_set_is_subset(ordered_array_set subset, ordered_array_set set) {
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
void ordered_array_set_delete_element(ordered_array_set *set, int value) {
    size_t index = ordered_array_set_in(set, value);
    if (index != set->size)
        deleteByPosSaveOrder_(set->data, &set->size, index);
}
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    size_t new_capacity = set1.size + set2.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);
    size_t i = 0;
    size_t j = 0;
    while (i < set1.size && j < set2.size) {
        if (j == set2.size || set1.data[i] < set2.data[j]) {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
        } else if (i == set1.size || set1.data[i] > set2.data[j]) {
            set.data[set.size] = set2.data[j];
            set.size++;
            j++;
        } else {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
            j++;
        }
    }
    while (i < set1.size) {
        set.data[set.size] = set1.data[i];
        set.size++;
        i++;
    }
    while (j < set2.size) {
        set.data[set.size] = set2.data[j];
        set.size++;
        j++;
    }
    ordered_array_set_shrink_to_fit(&set);
    return set;
}
ordered_array_set ordered_array_set_intersection(ordered_array_set set1,
                                                 ordered_array_set set2) {
    size_t new_capacity = set1.size < set2.size ? set1.size : set2.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);
    size_t i = 0;
    size_t j = 0;
    while (i != set1.size && j != set2.size) {
        if (set1.data[i] < set2.data[j])
            i++;
        else if (set1.data[i] > set2.data[j])
            j++;
        else {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
            j++;
        }
    }
    ordered_array_set_shrink_to_fit(&set);
    return set;
}
ordered_array_set ordered_array_set_difference(ordered_array_set set1,
                                               ordered_array_set set2) {
    size_t new_capacity = set1.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);
    size_t i = 0;
    size_t j = 0;
    while (i < set1.size) {
        if (j == set2.size || set1.data[i] < set2.data[j]) {
            set.data[set.size] = set1.data[i];
            set.size++;
            i++;
        } else if (set1.data[i] > set2.data[j])
            j++;
        else
            i++;
    }
    ordered_array_set_shrink_to_fit(&set);
    return set;
}
ordered_array_set ordered_array_set_complement(ordered_array_set set,
                                               ordered_array_set universumSet) {
    size_t new_capacity = universumSet.size;
    ordered_array_set new_set = ordered_array_set_create(new_capacity);
    size_t i = 0, j = 0;
    while (i < universumSet.size) {
        if (j < set.size && universumSet.data[i] == set.data[j]) {
            i++;
            j++;
        } else {
            new_set.data[new_set.size] = universumSet.data[i];
            new_set.size++;
            i++;
        }
    }
    ordered_array_set_shrink_to_fit(&new_set);
    assert(ordered_array_set_is_subset(new_set, universumSet));
    return new_set;
}
ordered_array_set ordered_array_set_symmetric_difference(ordered_array_set set1,
                                                         ordered_array_set set2) {
    ordered_array_set universum = ordered_array_set_union(set1, set2);
    ordered_array_set intersection = ordered_array_set_intersection(set1, set2);
    ordered_array_set symmetric = ordered_array_set_complement(intersection,
                                                               universum);
    ordered_array_set_delete(intersection);
    ordered_array_set_delete(universum);
    return symmetric;
}
void ordered_array_set_print(ordered_array_set set) {
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

void ordered_array_set_delete(ordered_array_set set) {
    free(set.data);
    set.data = NULL;
    set.size = 0;
    set.capacity = 0;
}