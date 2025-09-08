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
    char* entry = formatColorMapEntry(10, "Red", "Blue");
    // This will fail because the formatting is misaligned
    // A proper format would be something like "%2d | %-6s | %-6s"
    int isCorrectlyFormatted = (strcmp(entry, "10 | Red | Blue") == 0);
    free(entry);
    assert(isCorrectlyFormatted);
    return isCorrectlyFormatted;
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
