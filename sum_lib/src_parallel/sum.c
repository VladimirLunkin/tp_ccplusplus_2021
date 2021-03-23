#include "sum.h"
#include "pipes.h"
#include <unistd.h>
#include <sys/wait.h>


int sum_range(const int *arr, size_t begin, size_t end, int64_t *sum) {
    if (arr == NULL || sum == NULL) {
        return 1;
    }

    *sum = 0;

    size_t i_begin = begin / 10;

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

    pipes_t *pipes = create_pipes(num_cores);
    if (pipes == NULL) {
        return 1;
    }

    size_t current_proc = 0;
    for (; current_proc < num_cores; ++current_proc) {
        int pid = fork();
        if (pid == -1) {
            close_pipes(pipes);
            return 1;
        }
        if (pid == 0) {
            if (close_all_except_write_pipe(pipes, current_proc) != 0) {
                exit(EXIT_FAILURE);
            }

            size_t size_one_proc = (size_t)(size / num_cores);
            size_t begin = current_proc * size_one_proc;
            size_t end = (current_proc < num_cores - 1) ? begin + size_one_proc : size;

            sum_range(arr, begin, end, sum);

            if (write_pipe(pipes, current_proc, *sum) != 0) {
                close_pipes(pipes);
                exit(EXIT_FAILURE);
            }

            if (close_pipes(pipes) != 0) {
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        }
    }

    if (close_all_write_pipes(pipes) != 0) {
        return 1;
    }

    int status = 0;
    current_proc = 0;
    for (; current_proc < num_cores; ++current_proc) {
        if (wait(&status) < 0 || status != EXIT_SUCCESS) {
            close_pipes(pipes);
            return 1;
        }
    }

    *sum = 0;
    current_proc = 0;
    for (; current_proc < num_cores; ++current_proc) {
        int64_t small_sum = 0;

        if (read_pipe(pipes, current_proc, &small_sum) != 0) {
            close_pipes(pipes);
            return 1;
        }

        *sum += small_sum;
    }

    close_pipes(pipes);

    return 0;
}
