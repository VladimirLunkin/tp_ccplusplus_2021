#include "sum.h"


int calculate_sum(const int *arr, size_t size, int64_t *sum) {
    if (arr == NULL || sum == NULL || size < 1) {
        return NULL_ARGS;
    }

    *sum = 0;

    size_t i_end = (int)((size - 1) / UPPER_BOUND);
    for (size_t i = 0; i <= i_end; ++i) {
        for (size_t k = 0; k < UPPER_BOUND && k + UPPER_BOUND * i < size; ++k) {
            *sum += arr[k + UPPER_BOUND * i];
        }
    }

    return SUCCESS;
}
