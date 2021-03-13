#include "gtest/gtest.h"

extern "C" {
#include "string/string.h"
}

TEST(free_string, null_arguments) {
    ASSERT_EQ(1, free_string(nullptr));
}
TEST(free_string, correct_arguments) {
    auto *str = (string_t*)malloc(sizeof(string_t));
    str->str = (char*)malloc(10 * sizeof(char*));
    ASSERT_EQ(0, free_string(str));
}

TEST(create_string, alloc) {
    string_t *str = create_string();
    EXPECT_TRUE(str != nullptr && str->str != nullptr);
    free_string(str);
}

TEST(resize, null_arguments) {
    ASSERT_EQ(1, resize(nullptr));
}
TEST(resize, correct_arguments) {
    auto *str = create_string();
    EXPECT_EQ(0, resize(str));
    free_string(str);
}

TEST(add_symbol, null_arguments) {
    ASSERT_EQ(1, add_symbol(nullptr, 'a'));
}
TEST(add_symbol, correct_arguments) {
    auto *str = create_string();
    EXPECT_EQ(0, add_symbol(str, 'a'));
    EXPECT_STREQ("a", str->str);
    free_string(str);
}
TEST(add_symbol, logic) {
    auto *str = create_string();
    add_symbol(str, 'a');
    add_symbol(str, 'b');
    add_symbol(str, 'c');
    EXPECT_STREQ("abc", str->str);
    free_string(str);
}

TEST(clear_string, null_arguments) {
    ASSERT_EQ(1, clear_string(nullptr));
}
TEST(clear_string, correct_arguments) {
    auto *str = create_string();
    EXPECT_EQ(0, clear_string(str));
    EXPECT_STREQ("", str->str);
    free_string(str);
}
TEST(clear_string, logic) {
    auto *str = create_string();
    add_symbol(str, 'a');
    add_symbol(str, 'b');
    add_symbol(str, 'c');
    EXPECT_EQ(0, clear_string(str));
    EXPECT_STREQ("", str->str);
    free_string(str);
}

TEST(read_str, null_arguments) {
    ASSERT_EQ(1, read_str(nullptr, nullptr));
}
TEST(read_str, correct_arguments) {
    auto *str = create_string();
    FILE *fp = fopen(SOURCE_DIR"/data/db_1", "r");
    EXPECT_EQ(0, read_str(fp, str));
    EXPECT_STREQ("Огонь", str->str);
    EXPECT_EQ(10, str->size);
    free_string(str);
    fclose(fp);
}
