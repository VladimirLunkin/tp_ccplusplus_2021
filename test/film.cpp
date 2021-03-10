#include "gtest/gtest.h"

extern "C" {
#include "film/film.h"
}

#include <cmath>
#include <limits>


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
    if (film == nullptr) {
        FAIL() << "can't allocate memory";
    }
    film->movie_title = (char*)malloc(strlen(movie_title) + 1);
    if (film->movie_title == nullptr) {
        free(film);
        FAIL() << "can't allocate memory";
    }
    film->genre = (char*)malloc(strlen(genre) + 1);
    if (film->genre == nullptr) {
        free(film->movie_title);
        free(film);
        FAIL() << "can't allocate memory";
    }
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
    char data[] = "Огонь 2020 драма 7.7";
    film_t *film = create_film(movie_title, year_of_issue, genre, average_rating);
    EXPECT_TRUE(strcmp(film->movie_title, movie_title) == 0 &&
                film->year_of_issue == year_of_issue &&
                strcmp(film->genre, genre) == 0 &&
                is_equal(film->average_rating, average_rating));
    free_film(film);
}

TEST(create_film_str, null_arguments) {
    film_t *film = create_film_str(nullptr);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}
TEST(create_film_str, wrong_arguments_1) {
    char data[] = "123";
    film_t *film = create_film_str(data);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}
TEST(create_film_str, wrong_arguments_2) {
    char data[] = "Огонь 2020 драма";
    film_t *film = create_film_str(data);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}
TEST(create_film_str, wrong_arguments_3) {
    char data[] = "Огонь Огонь Огонь Огонь";
    film_t *film = create_film_str(data);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}
TEST(create_film_str, correct_arguments) {
    char data[] = "Огонь 2020 драма 7.7";
    film_t *film = create_film_str(data);
    EXPECT_TRUE(film != nullptr &&
                        strcmp(film->movie_title, "Огонь") == 0 &&
                        film->year_of_issue == 2020 &&
                        strcmp(film->genre, "драма") == 0 &&
                        is_equal(film->average_rating, 7.7));
    free_film(film);
}

TEST(print_film, null_arguments) {
    EXPECT_EQ(1, print_film(nullptr, nullptr));
}
TEST(print_film, file) {
    char file_name[] = "test_print_film";
    FILE *fptr = fopen(file_name, "w");
    film_t *film = create_film((char*)"Огонь", 2020, (char*)"драма", 7.7);
    EXPECT_EQ(0, print_film(fptr, film));
    fclose(fptr);
    remove(file_name);
    free_film(film);
}
