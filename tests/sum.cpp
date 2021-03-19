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

TEST(sum, correct_arguments) {
    int arr[100];
    std::fill_n(arr, 100, 1);
    ASSERT_EQ(99, sum(arr, 100));
}
