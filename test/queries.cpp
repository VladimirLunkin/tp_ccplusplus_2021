#include "gtest/gtest.h"
#include <cmath>
#include <limits>

extern "C" {
#include "film/queries.h"
}

bool is_equal(float x, float y) {
    return std::fabs(x - y) < std::numeric_limits<float>::epsilon();
}

bool cmp_film(film_t *l, film_t *r) {
    return (strcmp(l->movie_title, r->movie_title) == 0 &&
        l->year_of_issue == r->year_of_issue &&
        strcmp(l->genre, r->genre) == 0 &&
        is_equal(l->average_rating, r->average_rating));
}

bool cmp_films(films_t *l, films_t *r) {
    if (l->size != r->size) {
        return false;
    }

    for (int i = 0; i < l->size; ++i) {
        if (!cmp_film(l->films[i], r->films[i])) {
            return false;
        }
    }

    return true;
}

class TestQueries : public ::testing::Test {
protected:
    void SetUp() {
        fp = fopen(SOURCE_DIR"/data/db_2", "r");
        films = read_films_from_file(fp);
        empty_films = create_films(0);
    }
    void TearDown() {
        fclose(fp);
        free_films(films);
        free_films(empty_films);
    }
    FILE *fp;
    films_t *films;
    films_t *empty_films;
};

TEST_F(TestQueries, rating_range_null_arguments) {
    ASSERT_EQ(nullptr, rating_range(nullptr, 1.0f, 1.0f));
}
TEST_F(TestQueries, rating_range_wrong_arguments) {
    EXPECT_EQ(nullptr, rating_range(films, 2.0f, 1.0f));
}
TEST_F(TestQueries, rating_range_miss_range) {
    films_t *ans_films = rating_range(films, 1.0f, 2.0f);
    EXPECT_NE(nullptr, ans_films);

    EXPECT_TRUE(cmp_films(empty_films, ans_films));

    free_films(ans_films);
}
TEST_F(TestQueries, rating_range_correct_arguments) {
    FILE *ans_fp = fopen(SOURCE_DIR"/data/res/rating_range", "r");
    films_t *expected_films = read_films_from_file(ans_fp);

    films_t *ans_films = rating_range(films, 7.0f, 7.8f);
    EXPECT_NE(nullptr, ans_films);

    EXPECT_TRUE(cmp_films(expected_films, ans_films));

    free_films(ans_films);
    free_films(expected_films);
}

TEST_F(TestQueries, genre_of_films_null_arguments) {
    ASSERT_EQ(nullptr, genre_of_films(nullptr, nullptr));
}
TEST_F(TestQueries, genre_of_films_miss_range) {
    films_t *ans_films = genre_of_films(films, "ужасы");
    EXPECT_NE(nullptr, ans_films);

    EXPECT_TRUE(cmp_films(empty_films, ans_films));

    free_films(ans_films);
}
TEST_F(TestQueries, genre_of_films_correct_arguments) {
    FILE *ans_fp = fopen(SOURCE_DIR"/data/res/genre_of_films", "r");
    films_t *expected_films = read_films_from_file(ans_fp);

    films_t *ans_films = genre_of_films(films, "драма");
    EXPECT_NE(nullptr, ans_films);

    EXPECT_TRUE(cmp_films(expected_films, ans_films));

    free_films(ans_films);
    free_films(expected_films);
}

TEST_F(TestQueries, year_of_films_null_arguments) {
    ASSERT_EQ(nullptr, year_of_films(nullptr, 0));
}
TEST_F(TestQueries, year_of_films_miss_range) {
    films_t *ans_films = year_of_films(films, 100);
    EXPECT_NE(nullptr, ans_films);

    EXPECT_TRUE(cmp_films(empty_films, ans_films));

    free_films(ans_films);
}
TEST_F(TestQueries, year_of_films_correct_arguments) {
    FILE *ans_fp = fopen(SOURCE_DIR"/data/res/year_of_films", "r");
    films_t *expected_films = read_films_from_file(ans_fp);

    films_t *ans_films = year_of_films(films, 2002);
    EXPECT_NE(nullptr, ans_films);

    EXPECT_TRUE(cmp_films(expected_films, ans_films));

    free_films(ans_films);
    free_films(expected_films);
}
