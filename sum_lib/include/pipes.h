#ifndef SUM_LIB_INCLUDE_PIPES_H_
#define SUM_LIB_INCLUDE_PIPES_H_

#include <stdlib.h>

typedef struct {
    int **fd;
    size_t size;
} pipes_t;

pipes_t *create_pipes(size_t num_pipes);
int write_pipe(pipes_t *pipes, size_t num_pipe, int64_t num);
int read_pipe(pipes_t *pipes, size_t num_pipe, int64_t *num);
int close_all_write_pipes(pipes_t *pipes);
int close_all_except_write_pipe(pipes_t *pipes, size_t do_not_close);
int close_pipes(pipes_t *pipes);

#endif  // SUM_LIB_INCLUDE_PIPES_H_
