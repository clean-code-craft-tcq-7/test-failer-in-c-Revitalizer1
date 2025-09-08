#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "weatherreport.h"

// Implementation of weather report function
const char* weather_report(WeatherSensor* sensor) {
    WeatherData data = sensor->read();
    
    // Bug: There's an issue with the temperature condition checks
    if (data.temperature > 25) {
        return "Hot";
    } else if (data.temperature < 0) {  // Bug: Should check if temp < 10, but checks < 0
        if (data.precipitation > 20) {
            return "Snowy";
        }
    } else if (data.precipitation > 50) {
        return "Rainy";
    }
    
    return "Sunny";
}

// Test sensor implementation
typedef struct {
    WeatherSensor base;
    WeatherData testData;
} TestSensor;

static WeatherData readTestSensor(TestSensor* self) {
    return self->testData;
}

WeatherSensor* create_test_sensor(int temp, int humidity, int precip) {
    TestSensor* sensor = malloc(sizeof(TestSensor));
    sensor->testData.temperature = temp;
    sensor->testData.humidity = humidity;
    sensor->testData.precipitation = precip;
    sensor->base.read = (WeatherData(*)())readTestSensor;
    return (WeatherSensor*)sensor;
}
