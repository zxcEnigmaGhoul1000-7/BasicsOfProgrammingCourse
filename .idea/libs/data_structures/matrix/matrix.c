#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include "matrix.h"

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);

    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);

    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);

    free(m->values);
    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(ms + i);
    }

    free(ms->values);
    ms->values = NULL;
    ms->nRows = 0;
    ms->nCols = 0;
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        printf("input %d row:", i + 1);
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int n_matrices) {
    for (int i = 0; i < n_matrices; i++) {
        printf("input %lld matrix\n", i + 1);
        inputMatrix(ms + i);
        printf("\n");
    }
}

void outputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            printf("%d ", m->values[i][j]);
        }

        printf("\n");
    }
    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms + i);
    }
}

void swapRows(matrix *m, int i1, int i2) {
    int *temp = m->values[i1];
    m->values[i1] = m->values[i2];
    m->values[i2] = temp;
}

void swapColumns(matrix *m, int j1, int j2) {
    for (int i = 0; i < m->nRows; i++) {
        int temp = *(&m->values[i][j1]);
        *(&m->values[i][j1]) = *(&m->values[i][j2]);
        *(&m->values[i][j2]) = temp;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix *m, int (*criteria)(int*, int)) {
    int res_criteria[m->nRows];

    for(int i = 0; i < m->nRows; i++)
        res_criteria[i] = criteria(m->values[i], m->nCols);

    for (int i = 1; i < m->nRows; i++) {
        int key = res_criteria[i];
        int *address_key = m->values[i];
        int j = i - 1;

        while (j >= 0 && res_criteria[j] > key) {
            res_criteria[j + 1] = res_criteria[j];
            swapRows(m, j + 1, j);

            j -= 1;
        }

        res_criteria[j + 1] = key;
        m->values[j + 1] = address_key;
    }
}

void selectionSortColsMatrixByColCriteria(matrix *m, int (*criteria)(int*, int)) {
    int res_criteria[m->nCols];

    for (size_t i = 0; i < m->nCols; i++) {
        int temp[m->nRows];
        for (size_t j = 0; j < m->nRows; j++)
            temp[j] = m->values[j][i];

        res_criteria[i] = criteria(temp, m->nRows);
    }

    int value_min_idx;
    for (int i = 0; i < m->nCols; i++) {
        value_min_idx = i;

        for (int j = i + 1; j < m->nCols; j++)
            if (res_criteria[j] < res_criteria[value_min_idx])
                value_min_idx = j;

        int temp = *(&res_criteria[value_min_idx]);
        *(&res_criteria[value_min_idx]) = *(&res_criteria[i]);
        *(&res_criteria[i]) = temp;

        swapColumns(m, value_min_idx, i);
    }
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        fprintf(stderr, "Is not square matrix");
        exit(1);
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j && m->values[i][j] != 1) {
                return false;
            } else if (i != j && m->values[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }

    return true;
}

void transposeSquareMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        fprintf(stderr, "Is not square matrix");
        exit(1);
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            if (i != j) {
                int temp = m->values[i][j];
                m->values[i][j] = m->values[j][i];
                m->values[j][i] = temp;
            }
        }
    }
}

void transposeMatrix(matrix *m) {
    int** new_value = (int**) malloc(sizeof(int*) * m->nCols);

    for (int i = 0; i < m->nCols; i++) {
        new_value[i] = (int*) malloc(sizeof(int) * m->nRows);

        for (int j = 0; j < m->nRows; j++) {
            new_value[i][j] = m->values[j][i];
        }
    }

    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);
    free(m->values);

    m->values = new_value;
    swap(&m->nRows, &m->nCols);
}

position getMinValuePos(matrix m) {
    int min_value = m.values[0][0];
    position pos = {0, 0};

    for (int i = 1; i < m.nRows; i++) {
        for (int j = 1; j < m.nCols; j++) {
            if (m.values[i][j] < min_value) {
                min_value = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }

    return pos;
}

position getMaxValuePos(matrix m) {
    int max_value = m.values[0][0];
    position pos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max_value) {
                max_value = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }

    return pos;
}

matrix createMatrixFromArray(const int a[], int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }

    return m;
}

matrix* createArrayOfMatrixFromArray(const int values[], size_t nMatrices, size_t nRows, size_t nCols) {
    matrix* ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (size_t k = 0; k < nMatrices; k++) {
        for (size_t i = 0; i < nRows; i++) {
            for (size_t j = 0; j < nCols; j++) {
                ms[k].values[i][j] = values[l++];
            }
        }
    }

    return ms;
}