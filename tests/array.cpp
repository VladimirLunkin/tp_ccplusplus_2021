#include "gtest/gtest.h"

extern "C" {
#include "array.h"
}

TEST(free_arr, null_arguments) {
    ASSERT_EQ(1, free_arr(nullptr));
}
TEST(free_arr, correct_arguments) {
    array_t *arr = new array_t;
    arr->capacity = 5;
    arr->arr = new int[arr->capacity];
    std::fill_n(arr->arr, arr->capacity, 13);
    ASSERT_EQ(0, free_arr(nullptr));
}

TEST(create_arr, null_arguments) {
    array_t *arr = create_arr(0);

    EXPECT_NE(nullptr, arr);
    EXPECT_EQ(0, arr->capacity);

    free_arr(arr);
}
TEST(create_arr, correct_arguments) {
    array_t *arr = create_arr(10);

    EXPECT_NE(nullptr, arr);
    EXPECT_EQ(10, arr->capacity);

    free_arr(arr);
}

TEST(arr_read_from_file, null_arguments) {
    ASSERT_EQ(nullptr, arr_read_from_file(nullptr));
}
TEST(arr_read_from_file, wrong_path) {
    const char file_name[] = "qwerty";
    ASSERT_EQ(nullptr, arr_read_from_file(file_name));
}
TEST(arr_read_from_file, correct_arguments) {
    array_t *arr = create_arr(10);

    EXPECT_NE(nullptr, arr);
    EXPECT_EQ(10, arr->capacity);

    free_arr(arr);
}
