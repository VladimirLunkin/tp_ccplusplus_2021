#include "gtest/gtest.h"

extern "C" {
#include "list_of_films/list_of_films.h"
}

TEST(print_list_of_films, wrong_arguments_1) {
    EXPECT_NE(0, print_list_of_films(SOURCE_DIR"/data/db_2", 2, 1, (char*)"sas", 200));
}
TEST(print_list_of_films, wrong_arguments_2) {
    EXPECT_NE(0, print_list_of_films("asd", 2, 1, (char*)"sas", 200));
}
TEST(print_list_of_films, miss_range) {
    EXPECT_EQ(0, print_list_of_films(SOURCE_DIR"/data/db_2", 1, 10, (char*)"lhf", 200));
}
TEST(print_list_of_films, correct_arguments) {
    EXPECT_EQ(0, print_list_of_films(SOURCE_DIR"/data/db_2", 1, 10, (char*)"история", 1956));
}

/// не проходят два теста по причине директорий в симейк
/// допилить, подправить стринг, отправить на проверку
