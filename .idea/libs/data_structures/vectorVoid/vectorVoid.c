#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include "../../data_structures/vectorVoid//vectorVoid.h"

vectorVoid createVectorVoid(size_t capacity, size_t base_type_size) {
    if (capacity <= UINT64_MAX) {
        return (vectorVoid) {malloc(base_type_size * capacity), 0, capacity, base_type_size};
    } else {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void reserveV(vectorVoid *v, size_t new_capacity) {
    if (new_capacity > 0) {

        int *new_data = realloc(v->data, new_capacity * new_capacity * v->baseTypeSize);
        if (new_data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }

        v->data = new_data;
        v->capacity = new_capacity;

        if (new_capacity < v->size) {
            v->size = new_capacity;
        }

    } else {
        deleteVectorV(v);
    }
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void vectorShrinkToFitV(vectorVoid *v) {
    if (v->size != v->capacity) {
        v->data = (void *) realloc(v->data, v->size * v->baseTypeSize);
        v->capacity = v->size;
    }
}

bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

bool isFullV(vectorVoid *v) {
    return v->size == v->capacity;
}
void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    } else {
        char *source = (char *) v->data + index * v->baseTypeSize;
        memcpy(destination, source, v->baseTypeSize);
    }
}
void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    } else {
        char *dst = (char *) v->data + index * v->baseTypeSize;
        memcpy(dst, source, v->baseTypeSize);
    }
}
void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "bad alloc");
        exit(1);
    } else {
        v->size--;
    }
}
void pushBackV(vectorVoid *v, void *source) {
    if (v->capacity == 0) {
        v->capacity++;
    } else if (isFullV(v)) {
        reserveV(v, v->capacity * 2);
    }
    char *dst = (char *) v->data + v->size * v->baseTypeSize;
    memcpy(dst, source, v->baseTypeSize);
    v->size++;
}