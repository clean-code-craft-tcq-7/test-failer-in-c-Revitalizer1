#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the production code functions
extern "C" {
    // From tshirts.c
    char size(int cms);
    
    // From misaligned.c
    const char* formatColorPair(int colorCode, const char* majorColor);
    void generateColorMap(char* result, int maxSize);
    int printColorMap();
    
    // From weatherreport.c
    struct SensorReadings {
        int temperatureInC;
        int precipitation;
        int humidity;
        int windSpeedKMPH;
    };
    
    struct SensorReadings sensorStub_Normal();
    struct SensorReadings sensorStub_HighAlert();
    struct SensorReadings sensorStub_EdgeCase();
    struct SensorReadings sensorStub_CriticalTemp();
    const char* classifyWeather(struct SensorReadings data);
    void formatWeatherReport(struct SensorReadings data, char* report);
}

// ========== T-SHIRTS TESTS ==========
void testTShirtSizes() {
    printf("Testing T-shirt sizes...\n");
    
    // Original weak tests
    assert(size(37) == 'S');
    assert(size(40) == 'M');
    assert(size(43) == 'L');
    
    // Additional tests to expose the bug
    assert(size(38) == 'S'); // This will fail - 38 is not handled!
    assert(size(42) == 'M'); // This will fail - 42 is not handled!
    assert(size(0) == 'S');  // Edge case
    assert(size(100) == 'L'); // Edge case
    
    printf("T-shirt tests completed.\n");
}

// ========== MISALIGNED TESTS ==========
void testFormatting() {
    printf("Testing color formatting...\n");
    
    const char* result = formatColorPair(1, "Red");
    // This test will fail due to misalignment
    assert(strcmp(result, "1 | Red") == 0);
    
    result = formatColorPair(10, "SomeColor");
    // This test will fail due to misalignment with double digits
    assert(strcmp(result, "10 | SomeColor") == 0);
    
    printf("Formatting tests completed.\n");
}

void testColorMapGeneration() {
    printf("Testing color map generation...\n");
    
    char result[1024];
    generateColorMap(result, sizeof(result));
    
    // Test that the map contains expected content
    assert(strstr(result, "0 | White") != NULL);
    assert(strstr(result, "1 | Red") != NULL);
    assert(strstr(result, "4 | Violet") != NULL);
    
    // Test alignment - this will fail due to misalignment
    assert(strstr(result, "0 | White\n1 | Red\n") != NULL);
    
    printf("Color map generation tests completed.\n");
}

// ========== WEATHER REPORT TESTS ==========
void testRainy() {
    printf("Testing rainy weather...\n");
    
    struct SensorReadings readings = sensorStub_Normal();
    char report[200];
    formatWeatherReport(readings, report);
    printf("%s\n", report);
    assert(strstr(report, "rain") != NULL);
    
    printf("Rainy weather test completed.\n");
}

void testHighPrecipitation() {
    printf("Testing high precipitation...\n");
    
    struct SensorReadings readings = sensorStub_HighAlert();
    char report[200];
    formatWeatherReport(readings, report);
    printf("%s\n", report);
    // strengthen the assert to expose the bug
    // (function returns Sunny day, it should predict rain)
    assert(strlen(report) > 0);
    
    printf("High precipitation test completed.\n");
}

void testEdgeCase() {
    printf("Testing edge case weather...\n");
    
    struct SensorReadings readings = sensorStub_EdgeCase();
    char report[200];
    formatWeatherReport(readings, report);
    printf("%s\n", report);
    // This test will expose the bug in the condition logic
    assert(strstr(report, "Alert") != NULL);
    
    printf("Edge case test completed.\n");
}

void testCriticalTemp() {
    printf("Testing critical temperature...\n");
    
    struct SensorReadings readings = sensorStub_CriticalTemp();
    char report[200];
    formatWeatherReport(readings, report);
    printf("%s\n", report);
    // This test will expose the bug - high temp alone should trigger alert
    assert(strstr(report, "Alert") != NULL);
    
    printf("Critical temperature test completed.\n");
}

// ========== MAIN TEST RUNNER ==========
int main() {
    printf("=== Running All Tests ===\n\n");
    
    try {
        printf("1. T-Shirt Size Tests:\n");
        testTShirtSizes();
        printf("✓ T-shirt tests passed\n\n");
    } catch (...) {
        printf("✗ T-shirt tests failed\n\n");
    }
    
    try {
        printf("2. Color Map Tests:\n");
        testFormatting();
        testColorMapGeneration();
        printf("✓ Color map tests passed\n\n");
    } catch (...) {
        printf("✗ Color map tests failed\n\n");
    }
    
    try {
        printf("3. Weather Report Tests:\n");
        testRainy();
        testHighPrecipitation();
        testEdgeCase();
        testCriticalTemp();
        printf("✓ Weather report tests passed\n\n");
    } catch (...) {
        printf("✗ Weather report tests failed\n\n");
    }
    
    printf("=== All Tests Completed ===\n");
    return 0;
}
