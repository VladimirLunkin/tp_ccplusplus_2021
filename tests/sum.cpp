#include "gtest/gtest.h"

extern "C" {
#include "sum.h"
}

TEST(sum, null_arguments) {
    ASSERT_EQ(1, calculate_sum(nullptr, 0, nullptr));
}

TEST(sum, null_array) {
    int arr[100];
    std::fill_n(arr, 100, 0);
    int64_t sum = 0;
    ASSERT_EQ(1, calculate_sum(arr, 0, &sum));
}

TEST(sum, array_size_100) {
    const ssize_t size = 100;
    int arr[size];
    std::fill_n(arr, size, 1);
    int64_t sum = 0;
    EXPECT_EQ(0, calculate_sum(arr, size, &sum));
    EXPECT_EQ(100, sum);
}

TEST(sum, array_size_10000) {
    const ssize_t size = 10000;
    int arr[size];
    std::fill_n(arr, size, 1);
    int64_t sum = 0;
    EXPECT_EQ(0, calculate_sum(arr, size, &sum));
    EXPECT_EQ(10000, sum);
}

TEST(sum, array_size_1000000) {
    const ssize_t size = 1000000;
    int arr[size];
    std::fill_n(arr, size, 1);
    int64_t sum = 0;
    EXPECT_EQ(0, calculate_sum(arr, size, &sum));
    EXPECT_EQ(1000000, sum);
}

TEST(sum, array_size_235412) {
    const ssize_t size = 235412;
    int arr[size];
    std::fill_n(arr, size, 1);
    int64_t sum = 0;
    EXPECT_EQ(0, calculate_sum(arr, size, &sum));
    EXPECT_EQ(235412, sum);
}
