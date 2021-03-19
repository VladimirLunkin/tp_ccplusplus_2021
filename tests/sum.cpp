#include "gtest/gtest.h"

extern "C" {
#include "sum.h"
}

TEST(sum, null_arguments) {
    ASSERT_EQ(0, sum(nullptr, 0));
}

TEST(sum, null_array) {
    int arr[100];
    std::fill_n(arr, 100, 0);
    ASSERT_EQ(0, sum(arr, 0));
}

TEST(sum, array_size_100) {
    const ssize_t size = 100;
    int arr[size];
    std::fill_n(arr, size, 1);
    ASSERT_EQ(99, sum(arr, size));
}

TEST(sum, array_size_10000) {
    const ssize_t size = 10000;
    int arr[size];
    std::fill_n(arr, size, 1);
    ASSERT_EQ(9999, sum(arr, size));
}

TEST(sum, array_size_1000000) {
    const ssize_t size = 1000000;
    int arr[size];
    std::fill_n(arr, size, 1);
    ASSERT_EQ(999999, sum(arr, size));
}
