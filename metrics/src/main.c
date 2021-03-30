#include "sum.h"
#include "array.h"
#include <time.h>
#include <stdio.h>

int main() {
    FILE *fp = fopen(SOURCE_DIR"/generator/data.txt", "r");
    if (fp == NULL) {
        return 1;
    }

    array_t array = create_arr(0);
    if (arr_read(fp, &array)) {
        fclose(fp);
        return 1;
    }

    int64_t sum = 0;

    clock_t begin = clock();

    if (calculate_sum(array.arr, array.capacity, &sum) != 0) {
        free_arr(&array);
        fclose(fp);
        return 1;
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Результат работы: %ld\n", sum);
    printf("Время работы программы: %lf с\n", time_spent);

    free_arr(&array);
    fclose(fp);

    return 0;
}
