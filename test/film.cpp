#include "gtest/gtest.h"
#include <cmath>
#include <limits>

extern "C" {
#include "film/film.h"
}


bool is_equal(float x, float y) {
    return std::fabs(x - y) < std::numeric_limits<float>::epsilon();
}

TEST(free_film, null_arguments) {
    ASSERT_EQ(1, free_film(nullptr));
}
TEST(free_film, correct_arguments) {
    char movie_title[] = "Огонь";
    char genre[] = "драма";
    auto *film = (film_t*)malloc(sizeof(film_t));
    film->movie_title = (char*)malloc(strlen(movie_title) + 1);
    film->genre = (char*)malloc(strlen(genre) + 1);
    ASSERT_EQ(0, free_film(film));
}

TEST(create_film, null_arguments) {
    film_t *film = create_film(nullptr, 0, nullptr, 0);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}
TEST(create_film, correct_arguments) {
    char movie_title[] = "Огонь";
    unsigned short year_of_issue = 2020;
    char genre[] = "драма";
    float average_rating = 7.7;
    film_t *film = create_film(movie_title, year_of_issue, genre, average_rating);
    EXPECT_TRUE(strcmp(film->movie_title, movie_title) == 0 &&
                film->year_of_issue == year_of_issue &&
                strcmp(film->genre, genre) == 0 &&
                is_equal(film->average_rating, average_rating));
    free_film(film);
}

TEST(create_and_copy, null_arguments) {
    EXPECT_EQ(nullptr, create_and_copy(nullptr));
}
TEST(create_and_copy, correct_arguments) {
    char movie_title[] = "Огонь";
    unsigned short year_of_issue = 2020;
    char genre[] = "драма";
    float average_rating = 7.7;
    film_t film_for_copy = {movie_title, year_of_issue, genre, average_rating};
    film_t *film = create_and_copy(&film_for_copy);
    EXPECT_TRUE(strcmp(film->movie_title, movie_title) == 0 &&
                film->year_of_issue == year_of_issue &&
                strcmp(film->genre, genre) == 0 &&
                is_equal(film->average_rating, average_rating));
    free_film(film);
}

TEST(read_film_from_file, null_arguments) {
    film_t *film = read_film_from_file(nullptr);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}
TEST(read_film_from_file, empty_file) {
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_1", "r");
    film_t *film = read_film_from_file(fp);
    EXPECT_EQ(nullptr, film);
    free_film(film);
    fclose(fp);
}
TEST(read_film_from_file, wrong_data_1) {
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_2", "r");
    film_t *film = read_film_from_file(fp);
    EXPECT_EQ(nullptr, film);
    free_film(film);
    fclose(fp);
}
TEST(read_film_from_file, wrong_data_2) {
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_3", "r");
    film_t *film = read_film_from_file(fp);
    EXPECT_EQ(nullptr, film);
    free_film(film);
    fclose(fp);
}
TEST(read_film_from_file, correct_arguments) {
    FILE *fp = fopen(SOURCE_DIR"/data/db_1", "r");
    film_t *film = read_film_from_file(fp);
    EXPECT_TRUE(film != nullptr &&
                        strcmp(film->movie_title, "Огонь") == 0 &&
                        film->year_of_issue == 2020 &&
                        strcmp(film->genre, "драма") == 0 &&
                        is_equal(film->average_rating, 7.7));
    free_film(film);
    fclose(fp);
}

TEST(print_film, null_arguments) {
    EXPECT_EQ(1, print_film(nullptr, nullptr));
}
TEST(print_film, file) {
    char file_name[] = "test_print_film";
    FILE *fp = fopen(file_name, "w");
    film_t *film = create_film((char*)"Огонь", 2020, (char*)"драма", 7.7);
    EXPECT_EQ(0, print_film(fp, film));
    fclose(fp);
    remove(file_name);
    free_film(film);
}
