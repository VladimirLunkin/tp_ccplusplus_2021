#include "gtest/gtest.h"

extern "C" {
#include "pipes.h"
}

TEST(close_pipes, null_arguments) {
    ASSERT_EQ(1, close_pipes(nullptr));
}
TEST(close_pipes, correct_array) {
    auto *pipes = (pipes_t*)malloc(sizeof(pipes_t));
    pipes->size = 1;
    pipes->fd = (int**)malloc(pipes->size * sizeof(int*));
    pipes->fd[0] = (int*)malloc(2 * sizeof(int));
    pipe(pipes->fd[0]);
    EXPECT_EQ(0, close_pipes(pipes));
}


