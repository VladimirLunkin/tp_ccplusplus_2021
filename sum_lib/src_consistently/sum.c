#include "sum.h"


int calculate_sum(const int *arr, size_t size, int64_t *sum) {
    if (arr == NULL) {
        return 1;
    }

    *sum = 0;

    int i_end = (int)(size / 10) - 1;
    for (int i = 0; i <= i_end; ++i) {
        for (int k = 1; k < 10 || (k == 10 && i != i_end); ++k) {
            *sum += arr[k + 10 * i];
        }
    }

    return 0;
}
