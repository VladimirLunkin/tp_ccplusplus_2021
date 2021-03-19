#include "sum.h"
#include "array.h"
#include <time.h>
#include <stdio.h>

int main() {
    array_t *arr = arr_read_from_file("sefwe");
    if (arr == NULL) {
        return 1;
    }

    clock_t begin = clock();


    printf("Hello, World! %d\n", sum(arr->arr, arr->capacity));

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Время работы программы: %lf с\n", time_spent);

    free_arr(arr);

    return 0;
}
