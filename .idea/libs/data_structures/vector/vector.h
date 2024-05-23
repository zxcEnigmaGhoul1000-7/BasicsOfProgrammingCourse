#ifndef LAB_VECTOR_H
#define LAB_VECTOR_H

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

// возвращает структуру-дескриптор вектор из n значений.
vector create_vector(size_t capacity);

// изменяет количество памяти, выделенное под хранение элементов вектора.
void reserve(vector *v, size_t new_capacity);

// удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v);

// освобождает память, выделенную поднеиспользуемые элементы.
void shrinkToFit(vector *v);

// освобождает память, выделенную вектору.
void deleteVector(vector *v);

// проверки на то, является ли вектор пустым.
bool isEmpty(vector *v);

// проверки на то, является ли вектор полным.
bool isFull(vector *v);

// возвращает i-ый элемент вектора v.
int getVectorValue(vector *v, size_t i);

// добавляет элемент x в конец вектора.
void pushBack(vector *v, int x);

// удаляет последний элемент из вектора.
void popBack(vector *v);

// возвращает указатель на index-ый элемент вектора.
int* atVector(vector *v, size_t index);

// возвращает указатель на последний элемент вектора.
int* back(vector *v);

// возвращает указатель на нулевой элемент вектора.
int* front(vector *v);

#endif //LAB_VECTOR_H

