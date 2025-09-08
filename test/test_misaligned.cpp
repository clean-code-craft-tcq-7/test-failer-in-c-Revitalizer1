#include <gtest/gtest.h>
#include <string>
#include <cstring>

extern "C" {
    #include "../src/misaligned.h"
}

TEST(MisalignedTest, FormatColorPairTest) {
    // Test the formatting of color pairs
    char* formatted = format_color_pair(1, "White", "Blue");
    std::string expected = "       1 |       White |        Blue";
    
    // This will fail because the formatting in format_color_pair is misaligned
    EXPECT_STREQ(expected.c_str(), formatted);
    free(formatted);
}

TEST(MisalignedTest, ColorPairNumberTest) {
    // Test pair number calculation
    EXPECT_EQ(1, get_pair_number_from_colors("White", "Blue"));
    EXPECT_EQ(25, get_pair_number_from_colors("Violet", "Slate"));
}

TEST(MisalignedTest, ColorFromPairNumberTest) {
    // Test color retrieval
    ColorPair pair = get_color_from_pair_number(1);
    EXPECT_STREQ("White", pair.majorColor);
    EXPECT_STREQ("Blue", pair.minorColor);
}