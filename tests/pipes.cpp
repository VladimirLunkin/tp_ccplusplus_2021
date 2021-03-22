#include "gtest/gtest.h"

extern "C" {
#include "pipes.h"
}

TEST(close_pipes, null_argument) {
    ASSERT_NE(0, close_pipes(nullptr));
}
TEST(close_pipes, correct_argument) {
    auto *pipes = (pipes_t*)malloc(sizeof(pipes_t));

    const size_t Size = 1;
    pipes->fd = (int**)malloc(Size * sizeof(int*));
    pipes->size = Size;
    pipes->fd[0] = (int*)malloc(2 * sizeof(int));
    pipe(pipes->fd[0]);

    ASSERT_EQ(0, close_pipes(pipes));
}

TEST(create_pipes, null_argument) {
    pipes_t *pipes = create_pipes(0);

    EXPECT_NE(nullptr, pipes);
    EXPECT_EQ(0, pipes->size);

    close_pipes(pipes);
}
TEST(create_pipes, correct_argument) {
    size_t size = 10;
    pipes_t *pipes = create_pipes(size);

    EXPECT_NE(nullptr, pipes);
    EXPECT_NE(nullptr, pipes->fd);
    EXPECT_EQ(size, pipes->size);

    close_pipes(pipes);
}

TEST(write_pipe, null_arguments) {
    ASSERT_NE(0, write_pipe(nullptr, 0, 0));
}
TEST(write_pipe, correct_arguments) {
    size_t size = 1;
    pipes_t *pipes = create_pipes(size);

    int64_t expected_num = 12345;
    EXPECT_EQ(0, write_pipe(pipes, 0, expected_num));

    int byte_in_number = sizeof(int64_t);
    char *buf = new char[byte_in_number];
    read(pipes->fd[0][0], buf, byte_in_number);

    int64_t num = 0;
    for (int i = 0, p = 1; i < byte_in_number; ++i) {
        num += (u_int8_t)buf[i] * p;
        p *= 256;
    }

    EXPECT_EQ(expected_num, num);

    delete [] buf;
    close_pipes(pipes);
}

TEST(read_pipe, null_arguments) {
    ASSERT_NE(0, read_pipe(nullptr, 0, nullptr));
}
TEST(read_pipe, correct_arguments) {
    size_t size = 1;
    pipes_t *pipes = create_pipes(size);

    int64_t expected_num = 54321;
    write_pipe(pipes, 0, expected_num);

    int64_t num = 0;
    EXPECT_EQ(0, read_pipe(pipes, 0, &num));
    EXPECT_EQ(expected_num, num);

    close_pipes(pipes);
}

TEST(close_all_write_pipes, null_arguments) {
    ASSERT_NE(0, close_all_write_pipes(nullptr));
}
TEST(close_all_write_pipes, correct_arguments) {
    size_t Size = 10;
    pipes_t *pipes = create_pipes(Size);

    EXPECT_EQ(0, close_all_write_pipes(pipes));
    for (size_t i = 0; i < Size; ++i) {
        int64_t num = 1234;
        EXPECT_NE(0, write_pipe(pipes, i, num));
    }

    close_pipes(pipes);
}

TEST(close_all_except_write_pipe, null_arguments) {
    ASSERT_NE(0, close_all_except_write_pipe(nullptr, 0));
}
TEST(close_all_except_write_pipe, correct_arguments) {
    size_t Size = 10;
    pipes_t *pipes = create_pipes(Size);

    size_t do_not_close = 3;
    EXPECT_EQ(0, close_all_except_write_pipe(pipes, do_not_close));

    for (size_t i = 0; i < Size; ++i) {
        int64_t num = 0;
        EXPECT_NE(0, read_pipe(pipes, i, &num));
    }

    close_pipes(pipes);
}
