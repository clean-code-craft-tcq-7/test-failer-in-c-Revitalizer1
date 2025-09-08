#include "gtest/gtest.h"

extern "C" {
    void testTshirtSize();
    void testPrintColorMap();
    void testWeatherReport();
}

TEST(TShirt, Size) {
    testTshirtSize();
}

TEST(ColorMap, Print) {
    testPrintColorMap();
}

TEST(WeatherReport, Report) {
    testWeatherReport();
}
