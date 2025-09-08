#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Function to generate a single color map entry
char* formatColorMapEntry(int index, const char* majorColor, const char* minorColor) {
    // Allocate memory for the string (including null terminator)
    char* entry = (char*)malloc(50);
    if (entry) {
        sprintf(entry, "%d | %s | %s", index, majorColor, minorColor);
    }
    return entry;
}

// Function to test a color map entry format
int testColorMapEntryFormat() {
    // Create entries for a single digit number and double digit number
    char* entry1 = formatColorMapEntry(2, "Red", "Blue");
    char* entry2 = formatColorMapEntry(10, "Red", "Blue");
    char* entry3 = formatColorMapEntry(5, "Yellow", "Brown");  // Testing with longer color names
    
    // Test alignment requirements:
    // 1. Numbers should be right-aligned with padding (e.g., "%2d")
    // 2. Color names should be left-aligned with fixed width (e.g., "%-6s")
    
    // Compare with expected properly formatted strings
    int isCorrectlyFormatted1 = (strcmp(entry1, " 2 | Red     | Blue    ") == 0);
    int isCorrectlyFormatted2 = (strcmp(entry2, "10 | Red     | Blue    ") == 0);
    int isCorrectlyFormatted3 = (strcmp(entry3, " 5 | Yellow  | Brown   ") == 0);
    
    // Print actual vs expected to help with debugging
    printf("Expected: ' 2 | Red     | Blue    ', Got: '%s'\n", entry1);
    printf("Expected: '10 | Red     | Blue    ', Got: '%s'\n", entry2);
    printf("Expected: ' 5 | Yellow  | Brown   ', Got: '%s'\n", entry3);
    
    free(entry1);
    free(entry2);
    free(entry3);
    
    // This assertion will fail because the format doesn't match the requirements
    assert(isCorrectlyFormatted1 && isCorrectlyFormatted2 && isCorrectlyFormatted3);
    
    return isCorrectlyFormatted1 && isCorrectlyFormatted2 && isCorrectlyFormatted3;
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            char* entry = formatColorMapEntry(i * 5 + j, majorColor[i], minorColor[j]);
            printf("%s\n", entry);
            free(entry);
        }
    }
    return i * j;
}

int testPrintColorMap() {
    printf("\nPrint color map test\n");
    int formatResult = testColorMapEntryFormat();
    int result = printColorMap();
    assert(result == 25);
    assert(formatResult);
    printf("All is well (maybe!)\n");
    return 0;
}
