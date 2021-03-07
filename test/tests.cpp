#include "gtest/gtest.h"

extern "C" {
#include "utils/utils.h"
}

TEST(utils, ok) {
    ASSERT_EQ(widget_ok(1, 1), 1);
}

TEST(utils, not_ok) {
    ASSERT_EQ(widget_ok(1, 2), 0);
}

TEST(max, ok) {
    ASSERT_EQ(max(1, 2), 2);
}

TEST(max, not_ok) {
    ASSERT_EQ(max(6, 1), 6);
}
