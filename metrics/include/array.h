#ifndef METRICS_INCLUDE_ARRAY_H_
#define METRICS_INCLUDE_ARRAY_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *arr;
    size_t capacity;
} array_t;

array_t create_arr(size_t capacity);
int arr_read(FILE *fp, array_t *array);
int free_arr(array_t *array);

#endif  // METRICS_INCLUDE_ARRAY_H_
