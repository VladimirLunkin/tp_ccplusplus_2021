#include "gtest/gtest.h"

extern "C" {
#include "array.h"
}

bool cmp_arr(const int *arr1, const int *arr2, ssize_t size) {
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
    array_t array;
    array.capacity = 5;
    array.arr = (int*)calloc(array.capacity, sizeof(int));
    std::fill_n(array.arr, array.capacity, 13);

    EXPECT_EQ(0, free_arr(&array));
    EXPECT_EQ(0, array.capacity);
}

TEST(create_arr, null_arguments) {
    array_t array = create_arr(0);

    EXPECT_NE(nullptr, array.arr);
    EXPECT_EQ(0, array.capacity);

    free_arr(&array);
}
TEST(create_arr, correct_arguments) {
    array_t array = create_arr(10);

    EXPECT_NE(nullptr, array.arr);
    EXPECT_EQ(10, array.capacity);

    free_arr(&array);
}

TEST(arr_read, null_arguments) {
    ASSERT_NE(0, arr_read(nullptr, nullptr));
}
TEST(arr_read, miss_data_1) {
    const char file_name[] = SOURCE_DIR"/data/miss_data_1";
    FILE *fp = fopen(file_name, "r");

    array_t array = create_arr(0);

    EXPECT_NE(0, arr_read(fp, &array));

    fclose(fp);
}
TEST(arr_read, miss_data_2) {
    const char file_name[] = SOURCE_DIR"/data/miss_data_2";
    FILE *fp = fopen(file_name, "r");

    array_t array = create_arr(0);

    EXPECT_NE(0, arr_read(fp, &array));

    fclose(fp);
}
TEST(arr_read, data_1) {
    const char file_name[] = SOURCE_DIR"/data/data_1";
    FILE *fp = fopen(file_name, "r");

    array_t array = create_arr(0);
    int expected_arr[] = {1, 2, 3, 4, 5};

    EXPECT_EQ(0, arr_read(fp, &array));
    EXPECT_EQ(5, array.capacity);
    EXPECT_TRUE(cmp_arr(expected_arr, array.arr, array.capacity));

    free_arr(&array);
    fclose(fp);
}
