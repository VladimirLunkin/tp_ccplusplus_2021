#include "gtest/gtest.h"

extern "C" {
#include "film/film.h"
}

#include <cmath>
#include <limits>


bool is_equal(float x, float y) {
    return std::fabs(x - y) < std::numeric_limits<float>::epsilon();
}

TEST(parse_str_to_film, null_arguments) {
    film_t *film = parse_str_to_film(nullptr);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}

TEST(parse_str_to_film, wrong_arguments_1) {
    char data[] = "123";
    film_t *film = parse_str_to_film(data);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}

TEST(parse_str_to_film, wrong_arguments_2) {
    char data[] = "Огонь 2020 драма";
    film_t *film = parse_str_to_film(data);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}

TEST(parse_str_to_film, wrong_arguments_3) {
    char data[] = "Огонь Огонь Огонь Огонь";
    film_t *film = parse_str_to_film(data);
    EXPECT_EQ(nullptr, film);
    free_film(film);
}

TEST(parse_str_to_film, correct_arguments) {
    char data[] = "Огонь 2020 драма 7.7";
    film_t *film = parse_str_to_film(data);
    EXPECT_TRUE(strcmp(film->movie_title, "Огонь") == 0 &&
                        film->year_of_issue == 2020 &&
                        strcmp(film->genre, "драма") == 0 &&
                        is_equal(film->average_rating, 7.7));
    free_film(film);
}
