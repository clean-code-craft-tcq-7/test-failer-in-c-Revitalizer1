#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/weatherreport.h"

void test_weather_conditions() {
    // Testing normal conditions
    WeatherSensor* sunnySensor = create_test_sensor(25, 50, 0);
    assert(strcmp(weather_report(sunnySensor), "Sunny") == 0);
    free(sunnySensor);
    
    WeatherSensor* rainySensor = create_test_sensor(20, 60, 80);
    assert(strcmp(weather_report(rainySensor), "Rainy") == 0);
    free(rainySensor);
    
    WeatherSensor* snowySensor = create_test_sensor(-2, 45, 40);
    assert(strcmp(weather_report(snowySensor), "Snowy") == 0);
    free(snowySensor);
    
    // The bug is in the condition checking for temperature vs precipitation
    // Create a sensor with values that will trigger the bug
    // This will fail because there's a logic error in the conditions
    WeatherSensor* bugTriggerSensor = create_test_sensor(5, 45, 40);
    assert(strcmp(weather_report(bugTriggerSensor), "Snowy") == 0);
    free(bugTriggerSensor);
}

int main() {
    test_weather_conditions();
    printf("All weather report tests passed\n");
    return 0;
}