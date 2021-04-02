#include "sum.h"
#include "array.h"
#include <dlfcn.h>
#include <time.h>
#include <stdio.h>

typedef int (*func_sum_t)(const int *arr, unsigned long size, long *sum);

int metrics(func_sum_t func_sum, array_t array) {
    int64_t sum = 0;

    clock_t begin = clock();

    if (func_sum(array.arr, array.capacity, &sum) != 0) {
        return EXIT_FAILURE;
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\tРезультат работы: %ld\n", sum);
    printf("\tВремя работы программы: %lf с\n\n", time_spent);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    array_t array = create_arr(0);
    if (arr_read(fp, &array)) {
        fclose(fp);
        return EXIT_FAILURE;
    }
    fclose(fp);

    printf("## Последовательная реализация ##\n");
    if (metrics(calculate_sum, array)) {
        free_arr(&array);
        return EXIT_FAILURE;
    }

    void *library = dlopen(SOURCE_DIR"/build/libsum_parallel_lib.so", RTLD_LAZY);
    if (library == NULL) {
        free_arr(&array);
        return EXIT_FAILURE;
    }

    func_sum_t calculate_sum_parallel = dlsym(library, "calculate_sum");
    if (dlerror() != NULL)  {
        free_arr(&array);
        dlclose(library);
        return EXIT_FAILURE;
    }

    printf("## Параллельная реализация ##\n");
    if (metrics(calculate_sum_parallel, array)) {
        free_arr(&array);
        dlclose(library);
        return EXIT_FAILURE;
    }

    free_arr(&array);
    dlclose(library);

    return EXIT_SUCCESS;
}
