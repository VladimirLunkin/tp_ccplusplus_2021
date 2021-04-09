#ifndef SUM_LIB_INCLUDE_SUM_H_
#define SUM_LIB_INCLUDE_SUM_H_

#include <stdlib.h>

#define SUCCESS 0
#define NULL_ARGS 1
#define CREATE_PIPES_FAILED 2
#define READ_PIPE_FAILED 3
#define FORK_FAILED 4
#define WAIT_FAILED 5

#define UPPER_BOUND 10

int calculate_sum(const int *arr, size_t size, int64_t *sum);

#endif  // SUM_LIB_INCLUDE_SUM_H_
