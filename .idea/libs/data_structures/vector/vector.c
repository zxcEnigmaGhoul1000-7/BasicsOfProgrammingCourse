#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../data_structures/vector/vector.h"

vector create_vector(size_t capacity) {
    if (capacity <= UINT64_MAX) {
        return (vector) {malloc(sizeof(int) * capacity), 0, capacity};
    } else {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void reserve(vector *v, size_t new_capacity) {
    if (new_capacity > 0) {
        int *new_data = realloc(v->data, new_capacity * sizeof(int));
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
        deleteVector(v);
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->capacity = v->size;
}

void deleteVector(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    if (i >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    } else {
        return v->data[i];
    }
}

void pushBack(vector *v, int x) {
    if (v->capacity == 0) {
        v->capacity++;
    } else if (is_full(v)) {
        reserve(v, v->capacity * 2);
    }
    v->data[v->size++] = x;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "bad alloc");
        exit(1);
    } else {
        v->size--;
    }
}

int* atVector(vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[%d] is not exists\n", index);
        exit(1);
    } else {
        return &(v->data[index]);
    }
}

int* back(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error: Vector is empty\n");
        exit(1);
    } else {
        return &(v->data[v->size - 1]);
    }
}

int* front(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error: Vector is empty\n");
        exit(1);
    } else {
        return &(v->data[0]);
    }
}