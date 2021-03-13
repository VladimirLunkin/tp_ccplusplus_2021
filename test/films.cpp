#include "gtest/gtest.h"

extern "C" {
#include "film/films.h"
}

TEST(create_films, correct_arguments) {
    size_t capacity = 10;
    films_t *films = create_films(capacity);

    EXPECT_NE(nullptr, films);
    EXPECT_NE(nullptr, films->films);
    EXPECT_EQ(0, films->size);
    EXPECT_EQ(capacity, films->capacity);

    free(films->films);
    free(films);
}

TEST(free_films, null_arguments) {
    ASSERT_EQ(1, free_films(nullptr));
}
TEST(free_films, correct_arguments) {
    films_t *films = create_films(10);
    EXPECT_EQ(0, free_films(films));
}

TEST(read_films_from_file, null_arguments) {
    ASSERT_EQ(nullptr, read_films_from_file(nullptr));
}
TEST(read_films_from_file, wrong_data_1) {
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_2", "r");

    EXPECT_EQ(nullptr, read_films_from_file(fp));

    fclose(fp);
}
TEST(read_films_from_file, wrong_data_2) {
    FILE *fp = fopen(SOURCE_DIR"/wrong_data/db_4", "r");

    EXPECT_EQ(nullptr, read_films_from_file(fp));

    fclose(fp);
}
TEST(read_films_from_file, correct_arguments) {
    FILE *fp = fopen(SOURCE_DIR"/data/db_2", "r");
    films_t *films = read_films_from_file(fp);

    EXPECT_NE(nullptr, films);
    EXPECT_NE(nullptr, films->films);
    EXPECT_EQ(5, films->size);

    free_films(films);
    fclose(fp);
}

TEST(print_films, null_arguments) {
    ASSERT_EQ(1, print_films(nullptr, nullptr));
}
TEST(print_films, correct_arguments) {
    FILE *fp = fopen(SOURCE_DIR"/data/db_2", "r");
    films_t *films = read_films_from_file(fp);

    EXPECT_EQ(0, print_films(stdout, films));

    free_films(films);
    fclose(fp);
}

TEST(resize_films, null_arguments) {
    ASSERT_EQ(1, resize_films(nullptr));
}
TEST(resize_films, empty_films) {
    films_t *films = create_films(0);

    EXPECT_EQ(0, resize_films(films));
    EXPECT_EQ(2, films->capacity);

    free_films(films);
}
TEST(resize_films, correct_arguments) {
    FILE *fp = fopen(SOURCE_DIR"/data/db_2", "r");
    films_t *films = read_films_from_file(fp);

    EXPECT_EQ(0, resize_films(films));
    EXPECT_EQ(10, films->capacity);

    free_films(films);
    fclose(fp);
}

TEST(add_film_to_films, null_arguments) {
    ASSERT_EQ(1, add_film_to_films(nullptr, nullptr));
}
TEST(add_film_to_films, first_film) {
    films_t *films = create_films(0);

    char movie_title[] = "Огонь";
    unsigned short year_of_issue = 2020;
    char genre[] = "драма";
    float average_rating = 7.7f;

    film_t *film = create_film(movie_title, year_of_issue, genre, average_rating);

    EXPECT_EQ(0, add_film_to_films(films, film));
    EXPECT_EQ(1, films->size);

    EXPECT_STREQ(film->movie_title, films->films[0]->movie_title);
    EXPECT_EQ(film->year_of_issue, films->films[0]->year_of_issue);
    EXPECT_STREQ(film->genre, films->films[0]->genre);
    EXPECT_EQ(film->average_rating, films->films[0]->average_rating);

    free_film(film);
    free_films(films);
}
TEST(add_film_to_films, correct_arguments) {
    FILE *fp = fopen(SOURCE_DIR"/data/db_2", "r");
    films_t *films = read_films_from_file(fp);

    char movie_title[] = "Огонь";
    unsigned short year_of_issue = 2020;
    char genre[] = "драма";
    float average_rating = 7.7f;

    film_t *film = create_film(movie_title, year_of_issue, genre, average_rating);

    EXPECT_EQ(0, add_film_to_films(films, film));
    EXPECT_EQ(6, films->size);

    size_t i = films->size - 1;
    EXPECT_STREQ(film->movie_title, films->films[i]->movie_title);
    EXPECT_EQ(film->year_of_issue, films->films[i]->year_of_issue);
    EXPECT_STREQ(film->genre, films->films[i]->genre);
    EXPECT_EQ(film->average_rating, films->films[i]->average_rating);

    free_film(film);
    free_films(films);
    fclose(fp);
}
