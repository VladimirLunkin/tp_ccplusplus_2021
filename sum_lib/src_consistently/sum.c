#include "sum.h"


int calculate_sum(const int *arr, size_t size, int64_t *sum) {
    if (arr == NULL || sum == NULL || size < 1) {
        return NULL_ARGS;
    }

    *sum = 0;

    size_t i_end = (int)((size - 1) / 10);
    for (size_t i = 0; i <= i_end; ++i) {
        for (size_t k = 0; k < 10 && k + 10 * i < size; ++k) {
            *sum += arr[k + 10 * i];
        }
    }

    return SUCCESS;
}
