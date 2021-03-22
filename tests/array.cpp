#include "gtest/gtest.h"

extern "C" {
#include "array.h"
}

bool cmp_arr(int *arr1, int *arr2, ssize_t size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

TEST(free_arr, null_arguments) {
    ASSERT_NE(0, free_arr(nullptr));
}
TEST(free_arr, correct_arguments) {
    array_t *arr = (array_t*)malloc(sizeof(array_t));
    arr->capacity = 5;
    arr->arr = (int*)calloc(arr->capacity, sizeof(int));
    std::fill_n(arr->arr, arr->capacity, 13);
    ASSERT_EQ(0, free_arr(arr));
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
TEST(arr_read_from_file, miss_data_1) {
    const char file_name[] = SOURCE_DIR"/data/miss_data_1";
    ASSERT_EQ(nullptr, arr_read_from_file(file_name));
}
TEST(arr_read_from_file, miss_data_2) {
    const char file_name[] = SOURCE_DIR"/data/miss_data_2";
    ASSERT_EQ(nullptr, arr_read_from_file(file_name));
}
TEST(arr_read_from_file, data_1) {
    const char file_name[] = SOURCE_DIR"/data/data_1";
    array_t *arr = arr_read_from_file(file_name);
    int expected_arr[] = {1, 2, 3, 4, 5};

    EXPECT_NE(nullptr, arr);
    EXPECT_EQ(5, arr->capacity);
    EXPECT_TRUE(cmp_arr(expected_arr, arr->arr, arr->capacity));

    free_arr(arr);
}
