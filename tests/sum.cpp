#include "gtest/gtest.h"

extern "C" {
#include "sum.h"
}

TEST(sum, null_arguments) {
    ASSERT_EQ(0, sum(nullptr, 0));
}
