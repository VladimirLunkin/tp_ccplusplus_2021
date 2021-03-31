#include "sum.h"
#include "pipes.h"
#include <unistd.h>
#include <sys/wait.h>


int sum_of_one_proc(const int *arr, size_t size, int64_t *sum) {
    if (arr == NULL || sum == NULL || size < 1) {
        return 1;
    }

    *sum = 0;

    size_t i_end = (int)((size - 1) / 10);
    for (size_t i = 0; i <= i_end; ++i) {
        for (size_t k = 0; k < 10 && k + 10 * i < size; ++k) {
            *sum += arr[k + 10 * i];
        }
    }

    return 0;
}

int single_proc_handler(size_t proc_number, pipes_t *pipes, const int *arr, size_t size) {
    if (close_all_except_write_pipe(pipes, proc_number) != 0) {
        exit(EXIT_FAILURE);
    }

    int64_t sum = 0;
    sum_of_one_proc(arr, size, &sum);

    if (write_pipe(pipes, proc_number, sum) != 0) {
        close_pipes(pipes);
        exit(EXIT_FAILURE);
    }

    if (close_pipes(pipes) != 0) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
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
    size_t size_one_proc = (size_t)(size / num_cores);
    for (const int *arr_begin = arr; current_proc < num_cores; ++current_proc, arr_begin += size_one_proc) {
        int pid = fork();
        if (pid == -1) {
            close_pipes(pipes);
            return 1;
        }
        if (pid == 0) {
            if (current_proc + 1 == num_cores) {
                size_one_proc = size - current_proc * size_one_proc;
            }

            single_proc_handler(current_proc, pipes, arr_begin, size_one_proc);
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
