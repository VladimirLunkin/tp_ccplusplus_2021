#include "sum.h"


int64_t sum(const int *arr, size_t size) {
    if (arr == NULL) {
        return 0;
    }

    int64_t sum = 0;

    for (int k = 1; k <= 10; ++k) {
        for (int i = 0; k + 10 * i < size; ++i) {
            sum += arr[k + 10 * i];
        }
    }

    return sum;
}
