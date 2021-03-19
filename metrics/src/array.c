#include "array.h"
#include <stdio.h>


array_t *create_arr(size_t capacity) {
    array_t *arr = malloc(sizeof(array_t));
    if (arr == NULL) {
        return NULL;
    }

    arr->arr = calloc(capacity, sizeof(int));
    if (arr->arr == NULL) {
        return NULL;
    }

    arr->capacity = capacity;

    return arr;
}
array_t *arr_read_from_file(char *file_path) {
    if (file_path == NULL) {
        return NULL;
    }

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        return NULL;
    }

    size_t capacity = 0;
    if (fscanf(fp, "%zu", &capacity) != 1) {
        fclose(fp);
        return NULL;
    }

    array_t *arr = create_arr(capacity);
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < capacity; ++i) {
        if (fscanf(fp, "%d", &arr->arr[i]) != 1) {
            free_arr(arr);
            fclose(fp);
            return NULL;
        }
    }
    arr->capacity = capacity;

    fclose(fp);

    return arr;
}
int free_arr(array_t *arr) {
    if (arr == NULL) {
        return 1;
    }

    free(arr->arr);
    free(arr);

    return 0;
}
