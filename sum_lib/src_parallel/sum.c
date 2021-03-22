#include "sum.h"
#include "pipes.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int sum_range(const int *arr, size_t begin, size_t size, int64_t *sum) {
    if (arr == NULL || sum == NULL) {
        return 1;
    }

    *sum = 0;

    size_t i_begin = begin / 10;
    size_t end = begin + size;

    for (size_t i = i_begin; i <= end / 10; ++i) {
        size_t k = (i != i_begin) ? 0 : begin % 10;

        for (; k < 10 && k + 10 * i < end; ++k) {
            *sum += arr[k + 10 * i];
        }
    }

    return 0;
}

int calculate_sum(const int *arr, size_t size, int64_t *sum) {
    if (arr == NULL || sum == NULL || size < 1) {
        return 1;
    }

    size_t num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    size_t small_size = (size_t)(size / num_cores);

    pipes_t *pipes = create_pipes(num_cores);
    if (pipes == NULL) {
        return 1;
    }

    int pid = 0;
    size_t current_proc = 0;
    for (; current_proc < num_cores; ++current_proc) {
        pid = fork();
        if (pid == -1) {
            return 1;
        }
        if (pid == 0) {
            break;
        }
    }

    if (pid != 0 && close_write_pipes(pipes) != 0) {
        return 1;
    }

    if (pid == 0) {
        if (close_read_pipes(pipes, current_proc) != 0) {
            exit(EXIT_FAILURE);
        }

        size_t begin = current_proc * small_size;
        if (current_proc + 1 == num_cores) {
            small_size = size - (num_cores - 1) * small_size;
        }

        int64_t curr_sum = 0;
        if (sum_range(arr, begin, small_size, &curr_sum) != 0) {
            exit(EXIT_FAILURE);
        }

        if (write_pipe(pipes, current_proc, curr_sum) != 0) {
            exit(EXIT_FAILURE);
        }

        if (close_pipes(pipes) != 0) {
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    int status = 0;
    current_proc = 0;
    for (; current_proc < num_cores; ++current_proc) {
        pid = wait(&status);
        printf("proc_%zu pid=%d STATUS: %d\n", current_proc, pid, status);
        // проверить статус
    }

    *sum = 0;
    current_proc = 0;
    for (; current_proc < num_cores; ++current_proc) {
        int64_t small_sum = 0;

        if (read_pipe(pipes, current_proc, &small_sum) != 0) {
            return 1;
        }

        *sum += small_sum;
        printf("sum = %ld; small_sum = %ld\n", *sum, small_sum);
    }

    close_pipes(pipes);

    return 0;
}
