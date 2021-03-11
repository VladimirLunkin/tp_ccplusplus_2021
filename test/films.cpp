#include "gtest/gtest.h"

extern "C" {
#include "film/films.h"
}


TEST(free_films, null_arguments) {
    ASSERT_EQ(1, free_films(nullptr, 0));
}
TEST(free_films, correct_arguments) {
    size_t size = 10;
    auto films = (film_t**)malloc(size * sizeof(film_t*));
    for (int i = 0; i < size; ++i) {
        FILE *fp = fopen(SOURCE_DIR"/data/db_1", "r");
        films[i] = read_film_from_file(fp);
        fclose(fp);
    }
    EXPECT_EQ(0, free_films(films, size));
    free(films);
}

TEST(read_films_from_file, null_arguments) {
    ASSERT_EQ(1, read_films_from_file(nullptr, nullptr, nullptr));
}
TEST(read_films_from_file, wrong_data_1) {
    size_t size = 0;
    film_t **films = nullptr;
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_2", "r");
    EXPECT_EQ(1, read_films_from_file(fp, &films, &size));
    free_films(films, size);
    fclose(fp);
}
TEST(read_films_from_file, wrong_data_2) {
    size_t size = 0;
    film_t **films = nullptr;
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_4", "r");
    EXPECT_EQ(1, read_films_from_file(fp, &films, &size));
    free_films(films, size);
    fclose(fp);
}
TEST(read_films_from_file, correct_arguments) {
    size_t size = 0;
    film_t **films = nullptr;
    FILE *fp = fopen(SOURCE_DIR"/data/db_2", "r");
    EXPECT_EQ(0, read_films_from_file(fp, &films, &size));
    free_films(films, size);
    fclose(fp);
}

TEST(print_films, null_arguments) {
    ASSERT_EQ(1, print_films(nullptr, nullptr, 0));
}
TEST(print_films, correct_arguments) {
    size_t size = 0;
    film_t **films = nullptr;
    FILE *fp = fopen(SOURCE_DIR"/data/db_2", "r");
    read_films_from_file(fp, &films, &size);
    EXPECT_EQ(0, print_films(stdout, films, size));
    free_films(films, size);
    fclose(fp);
}
