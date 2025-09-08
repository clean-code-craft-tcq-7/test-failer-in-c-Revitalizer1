#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weatherreport.h"

struct SensorReadings {
    int temperatureInC;
    int precipitation;
    int humidity;
    int windSpeedKMPH;
};

// This is a stub for a weather sensor. For the sake of testing 
// we create a stub that generates weather data and allows us to
// test the other parts of this application in isolation
// without needing the actual Sensor during development

struct SensorReadings sensorStub_Normal() {
    struct SensorReadings readings;
    readings.temperatureInC = 26;
    readings.precipitation = 70;
    readings.humidity = 85;
    readings.windSpeedKMPH = 10;
    return readings;
}

struct SensorReadings sensorStub_HighAlert() {
    struct SensorReadings readings;
    readings.temperatureInC = 30;
    readings.precipitation = 95;
    readings.humidity = 92;
    readings.windSpeedKMPH = 55; // High temp, precipitation, humidity, wind
    return readings;
}

struct SensorReadings sensorStub_EdgeCase() {
    struct SensorReadings readings;
    readings.temperatureInC = 25;
    readings.precipitation = 60;
    readings.humidity = 70;
    readings.windSpeedKMPH = 50; // Edge values to test boundary conditions
    return readings;
}

struct SensorReadings sensorStub_CriticalTemp() {
    struct SensorReadings readings;
    readings.temperatureInC = 35;
    readings.precipitation = 45;
    readings.humidity = 65;
    readings.windSpeedKMPH = 25; // Very high temperature
    return readings;
}

// Separate concern: Determine weather conditions
const char* classifyWeather(struct SensorReadings data) {
    if(data.temperatureInC > 30) {
        if(data.precipitation >= 60 && data.windSpeedKMPH > 50) {
            return "Alert, Stormy with heavy rain";
        }
    }
    if(data.precipitation >= 60 && data.windSpeedKMPH > 50) {
        return "Alert, Stormy with heavy rain";
    }
    return "Sunny Day";
}

// Separate concern: Format weather report
void formatWeatherReport(struct SensorReadings data, char* report) {
    const char* condition = classifyWeather(data);
    sprintf(report, "Temperature %d C, Precipitation %d%%, Humidity %d%%, WindSpeed %d kmph - %s",
            data.temperatureInC, data.precipitation, data.humidity, data.windSpeedKMPH, condition);
}

// Implementation of weather report function
const char* weather_report(WeatherSensor* sensor) {
    WeatherData data = sensor->read();
    
    // Bug: There's an issue with the temperature condition checks
    if (data.temperature > 25) {
        return "Hot";
    } else if (data.temperature < 10) {
        if (data.precipitation > 20) {
            // Bug: doesn't correctly handle the case where temp is between 0 and 10
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

#ifdef UNIT_TEST
// Original stub sensor that doesn't expose the bug
static WeatherData weatherSensorStub() {
    WeatherData data = {24, 50, 0};
    return data;
}

int main() {
    WeatherSensor sensor = {weatherSensorStub};
    assert(weather_report(&sensor) == "Sunny");
    printf("All is well (maybe!)\n");
    return 0;
}
#endif

// Production code main function - for standalone execution
#ifndef LIB_MODE
int main() {
    printf("Weather reporting system\n");
    
    struct SensorReadings readings = sensorStub_Normal();
    char report[200];
    formatWeatherReport(readings, report);
    printf("Current weather: %s\n", report);
    
    return 0;
}
#endif
