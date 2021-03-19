#ifndef HW_2_ARRAY_H
#define HW_2_ARRAY_H

#include <stdlib.h>

typedef struct {
    int *arr;
    size_t capacity;
} array_t;

array_t *create_arr(size_t);
array_t *arr_read_from_file(char *);
int free_arr(array_t *);

#endif //HW_2_ARRAY_H
