#ifndef METRICS_INCLUDE_ARRAY_H_
#define METRICS_INCLUDE_ARRAY_H_

#include <stdlib.h>

typedef struct {
    int *arr;
    size_t capacity;
} array_t;

array_t *create_arr(size_t);
array_t *arr_read_from_file(const char *);
int free_arr(array_t *);

#endif  // METRICS_INCLUDE_ARRAY_H_
