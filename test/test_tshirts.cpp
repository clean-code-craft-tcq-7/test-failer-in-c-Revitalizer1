#include <gtest/gtest.h>

extern "C" {
    #include "../src/tshirts.h"
}

TEST(TShirtTest, SizeClassification) {
    // Test the standard cases
    EXPECT_EQ('S', size(37));
    EXPECT_EQ('S', size(38));
    EXPECT_EQ('M', size(40));
    EXPECT_EQ('M', size(41));  // This will fail because size 41 is not handled correctly
    EXPECT_EQ('M', size(42));
    EXPECT_EQ('L', size(43));
    EXPECT_EQ('L', size(44));
}