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
        return 1;
    }

    free_arr(array);

    size_t capacity = 0;
    if (fscanf(fp, "%zu", &capacity) != 1) {
        return 1;
    }

    *array = create_arr(capacity);

    for (int i = 0; i < capacity; ++i) {
        if (fscanf(fp, "%d", &array->arr[i]) != 1) {
            free_arr(array);
            return 1;
        }
    }
    array->capacity = capacity;

    return 0;
}
int free_arr(array_t *array) {
    if (array == NULL) {
        return 1;
    }

    free(array->arr);

    array->arr = NULL;
    array->capacity = 0;

    return 0;
}
