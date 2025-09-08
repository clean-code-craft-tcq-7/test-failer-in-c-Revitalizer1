#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/misaligned.h"

// Test the formatting of a color pair entry
void test_color_pair_formatting() {
    // This test will fail because of misalignment in the format_color_pair function
    char* formatted = format_color_pair(1, "White", "Blue");
    char* expected = "       1 |       White |        Blue";
    assert(strcmp(formatted, expected) == 0);
    free(formatted);
    
    formatted = format_color_pair(10, "Red", "Slate");
    expected = "      10 |         Red |       Slate";
    assert(strcmp(formatted, expected) == 0);
    free(formatted);
}

// Test the color pair number calculation
void test_color_pair_number() {
    assert(get_pair_number_from_colors("White", "Blue") == 1);
    assert(get_pair_number_from_colors("White", "Orange") == 2);
    assert(get_pair_number_from_colors("Violet", "Slate") == 25);
}

// Test color retrieval from pair number
void test_color_from_pair_number() {
    ColorPair pair = get_color_from_pair_number(1);
    assert(strcmp(pair.majorColor, "White") == 0);
    assert(strcmp(pair.minorColor, "Blue") == 0);
    
    pair = get_color_from_pair_number(10);
    assert(strcmp(pair.majorColor, "Red") == 0);
    assert(strcmp(pair.minorColor, "Slate") == 0);
}

int main() {
    test_color_pair_formatting();
    test_color_pair_number();
    test_color_from_pair_number();
    printf("All misaligned tests passed\n");
    return 0;
}