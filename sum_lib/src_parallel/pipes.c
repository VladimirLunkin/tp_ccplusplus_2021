#include "pipes.h"
#include <unistd.h>

static const int byte_in_number = 8;
static inline u_int8_t get_byte(int64_t num, int rank) {
    return (num >> (rank * byte_in_number)) & 0xFF;
}
static inline int int_to_byte_char(int64_t num, char *str) {
    if (str == NULL) {
        return 1;
    }

    for (int i = 0; i < byte_in_number; ++i) {
        char byte = get_byte(num, i);
        str[i] = byte;
    }

    return 0;
}
static inline int byte_char_to_int(const char *str, int64_t *num) {
    if (str == NULL || num == NULL) {
        return 1;
    }

    *num = 0;
    for (int i = 0, p = 1; i < byte_in_number; ++i) {
        *num += (u_int8_t)str[i] * p;
        p *= 256;
    }

    return 0;
}

pipes_t *create_pipes(size_t num_pipes) {
    pipes_t *pipes = malloc(sizeof(pipes_t));
    if (pipes == NULL) {
        return NULL;
    }

    pipes->fd = malloc(num_pipes * sizeof(int*));
    if (pipes->fd == NULL) {
        free(pipes);
        return NULL;
    }

    for (int i = 0; i < num_pipes; ++i) {
        pipes->fd[i] = malloc(2 * sizeof(int));
        if (pipes->fd[i] == NULL) {
            close_pipes(pipes);
            return NULL;
        }

        if (pipe(pipes->fd[i]) != 0) {
            close_pipes(pipes);
            return NULL;
        }
    }

    pipes->size = num_pipes;

    return pipes;
}
int write_pipe(pipes_t *pipes, size_t num_pipe, int64_t num) {
    if (pipes == NULL) {
        return 1;
    }

    char *buf = malloc(byte_in_number);
    if (buf == NULL) {
        return 1;
    }

    int_to_byte_char(num, buf);

    if (write(pipes->fd[num_pipe][1], buf, byte_in_number) == -1) {
        free(buf);
        return 1;
    }

    free(buf);

    return 0;
}
int read_pipe(pipes_t *pipes, size_t num_pipe, int64_t *num) {
    if (pipes == NULL) {
        return 1;
    }

    char *buf = malloc(byte_in_number);
    if (buf == NULL) {
        return 1;
    }

    if (read(pipes->fd[num_pipe][0], buf, byte_in_number) == -1) {
        free(buf);
        return 1;
    }

    byte_char_to_int(buf, num);

    free(buf);

    return 0;
}
int close_all_write_pipes(pipes_t *pipes) {
    if (pipes == NULL || pipes->fd == NULL) {
        return 1;
    }

    for (size_t i = 0; i < pipes->size; ++i) {
        close(pipes->fd[i][1]);
    }

    return 0;
}
int close_all_except_write_pipe(pipes_t *pipes, size_t do_not_close) {
    if (pipes == NULL || pipes->fd == NULL) {
        return 1;
    }

    for (size_t i = 0; i < pipes->size; ++i) {
        close(pipes->fd[i][0]);
        if (i != do_not_close) {
            close(pipes->fd[i][1]);
        }
    }

    return 0;
}
int close_pipes(pipes_t *pipes) {
    if (pipes == NULL) {
        return 1;
    }

    for (size_t i = 0; i < pipes->size; ++i) {
        close(pipes->fd[i][0]);
        close(pipes->fd[i][1]);
        free(pipes->fd[i]);
    }

    free(pipes->fd);
    free(pipes);

    return 0;
}
