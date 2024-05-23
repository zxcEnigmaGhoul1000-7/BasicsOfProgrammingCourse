#ifndef LAB_VECTORVOID_H
#define LAB_VECTORVOID_H

#include <limits.h>
#include <stdbool.h>

typedef struct vectorVoid {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; // размер базового типа:
// например, если вектор хранит int -
// то поле baseTypeSize = sizeof(int)
// если вектор хранит float -
// то поле baseTypeSize = sizeof(float)
} vectorVoid;

// возвращает структуру-дескриптор вектор из n значений.
vectorVoid createVectorVoid(size_t capacity, size_t base_type_size);

// изменяет количество памяти, выделенное под хранение элементов вектора.
void reserveV(vectorVoid *v, size_t new_capacity);

// удаляет элементы из контейнера, но не освобождает выделенную память.
void clearV(vectorVoid *v);

// освобождает память, выделенную под неиспользуемые элементы.
void vectorShrinkToFitV(vectorVoid *v);

// освобождает память, выделенную вектору.
void deleteVectorV(vectorVoid *v);

// проверки на то, является ли вектор пустым.
bool isEmptyV(vectorVoid *v);

// проверки на то, является ли вектор полным.
bool isFullV(vectorVoid *v);

// записывает по адресу destination index-ый элемент вектора v.
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

// записывает на index-ый элемент вектора v значение, расположенное по адресу source;
void setVectorValueV(vectorVoid *v, size_t index, void *source);

// удаляет последний элемент из вектора.
void popBackV(vectorVoid *v);

// добавляет элемент x в конец вектора.
void pushBackV(vectorVoid *v, void *source);

#endif //LAB_VECTORVOID_H
