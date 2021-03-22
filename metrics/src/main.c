#include "sum.h"
#include "array.h"
#include <time.h>
#include <stdio.h>

int main() {
    array_t *arr = arr_read_from_file(SOURCE_DIR"/generator/data.txt");
    if (arr == NULL) {
        return 1;
    }

    int64_t sum = 0;

    clock_t begin = clock();

    if (calculate_sum(arr->arr, arr->capacity, &sum) != 0) {
        return 1;
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Результат работы: %ld\n", sum);
    printf("Время работы программы: %lf с\n", time_spent);

    free_arr(arr);

    return 0;
}
