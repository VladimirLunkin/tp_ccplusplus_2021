#include "array.h"
#include <stdio.h>


array_t create_arr(size_t capacity) {
    array_t array = {NULL, 0};

    array.arr = calloc(capacity, sizeof(int));
    if (array.arr == NULL) {
        return array;
    }

    array.capacity = capacity;

    return array;
}
int arr_read(FILE *fp, array_t *array) {
    if (fp == NULL || array == NULL) {
        return NULL_ARGS;
    }

    free_arr(array);

    size_t capacity = 0;
    if (fscanf(fp, "%zu", &capacity) != 1) {
        return FSCANF_FAILED;
    }

    *array = create_arr(capacity);

    for (int i = 0; i < capacity; ++i) {
        if (fscanf(fp, "%d", &array->arr[i]) != 1) {
            free_arr(array);
            return FSCANF_FAILED;
        }
    }
    array->capacity = capacity;

    return SUCCESS;
}
int free_arr(array_t *array) {
    if (array == NULL) {
        return NULL_ARGS;
    }

    free(array->arr);

    array->arr = NULL;
    array->capacity = 0;

    return SUCCESS;
}
