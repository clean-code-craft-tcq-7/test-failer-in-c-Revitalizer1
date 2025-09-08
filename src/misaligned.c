#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* majorColor;
    const char* minorColor;
} ColorPair;

const char* majorColors[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColors[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

// Format a single color pair entry
char* format_color_pair(int pairNumber, const char* majorColor, const char* minorColor) {
    // Bug: This formatting causes misalignment
    char* result = malloc(50);
    sprintf(result, "%d | %s | %s", pairNumber, majorColor, minorColor);
    return result;
}

ColorPair get_color_from_pair_number(int pairNumber) {
    ColorPair colorPair;
    int zeroBasedPairNumber = pairNumber - 1;
    int majorIndex = zeroBasedPairNumber / 5;
    int minorIndex = zeroBasedPairNumber % 5;
    
    colorPair.majorColor = majorColors[majorIndex];
    colorPair.minorColor = minorColors[minorIndex];
    return colorPair;
}

int get_pair_number_from_colors(const char* major, const char* minor) {
    int majorIndex = -1;
    int minorIndex = -1;
    
    for (int i = 0; i < 5; i++) {
        if(strcmp(majorColors[i], major) == 0) {
            majorIndex = i;
            break;
        }
    }
    
    for (int i = 0; i < 5; i++) {
        if(strcmp(minorColors[i], minor) == 0) {
            minorIndex = i;
            break;
        }
    }
    
    if (majorIndex == -1 || minorIndex == -1) {
        return -1;
    }
    
    return majorIndex * 5 + minorIndex + 1;
}

void print_color_map() {
    int totalPairCount = 5 * 5;
    
    printf("Color Code Reference Chart:\n");
    printf("Pair No. | Major Color | Minor Color\n");
    
    for(int pairNumber = 1; pairNumber <= totalPairCount; pairNumber++) {
        ColorPair colorPair = get_color_from_pair_number(pairNumber);
        char* formattedLine = format_color_pair(
            pairNumber, 
            colorPair.majorColor, 
            colorPair.minorColor
        );
        printf("%s\n", formattedLine);
        free(formattedLine);
    }
}