#include "gtest/gtest.h"

extern "C" {
#include "film/films.h"
}

#include <cmath>
#include <limits>


bool is_equal(float x, float y) {
    return std::fabs(x - y) < std::numeric_limits<float>::epsilon();
}

TEST(free_films, null_arguments) {
    ASSERT_EQ(1, free_films(nullptr));
}
//TEST(free_films, correct_arguments) {
//
//}

