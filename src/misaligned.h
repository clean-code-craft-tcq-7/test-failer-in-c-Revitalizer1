#ifndef MISALIGNED_H
#define MISALIGNED_H

typedef struct {
    const char* majorColor;
    const char* minorColor;
} ColorPair;

// Function to print the color map
void print_color_map();

// Function to get individual color pair
ColorPair get_color_from_pair_number(int pairNumber);

// Function to format a single color pair entry
char* format_color_pair(int pairNumber, const char* majorColor, const char* minorColor);

// Function to get the total number of pairs
int get_pair_number_from_colors(const char* majorColor, const char* minorColor);

#endif // MISALIGNED_H