#include <gtest/gtest.h>
#include <string>
#include <cstring>

extern "C" {
    #include "../src/weatherreport.h"
}

TEST(WeatherReportTest, WeatherConditions) {
    // Test normal conditions
    WeatherSensor* sunnySensor = create_test_sensor(25, 50, 0);
    EXPECT_STREQ("Sunny", weather_report(sunnySensor));
    free(sunnySensor);
    
    WeatherSensor* rainySensor = create_test_sensor(20, 60, 80);
    EXPECT_STREQ("Rainy", weather_report(rainySensor));
    free(rainySensor);
    
    WeatherSensor* snowySensor = create_test_sensor(-2, 45, 40);
    EXPECT_STREQ("Snowy", weather_report(snowySensor));
    free(snowySensor);
    
    // The bug is in the condition checking for temperature vs precipitation
    // This will fail because of the logic error in the conditions
    // Temperature between 0-10 with precipitation > 20 should be "Snowy"
    WeatherSensor* bugTriggerSensor = create_test_sensor(5, 45, 40);
    EXPECT_STREQ("Snowy", weather_report(bugTriggerSensor));
    free(bugTriggerSensor);
}