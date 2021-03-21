#ifndef SUM_LIB_INCLUDE_PIPES_H_
#define SUM_LIB_INCLUDE_PIPES_H_

#include <stdlib.h>

typedef struct {
    int **fd;
    size_t size;
} pipes_t;

pipes_t *create_pipes(size_t);
int write_pipe(pipes_t *, size_t, int64_t);
int read_pipe(pipes_t *, size_t, int64_t *);
int close_write_pipes(pipes_t *);
int close_pipes_read(pipes_t *, size_t);
int close_pipes(pipes_t *);

#endif  // SUM_LIB_INCLUDE_PIPES_H_
