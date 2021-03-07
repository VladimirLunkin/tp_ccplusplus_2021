#include "gtest/gtest.h"

extern "C" {
#include "film/film.h"
}

TEST(utils, ok) {
    ASSERT_EQ(1, 1);
}
