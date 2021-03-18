#include "gtest/gtest.h"

extern "C" {
#include "sum.h"
}

TEST(sum, correct_arguments) {
    ASSERT_EQ(15, sum(5, 10));
}
