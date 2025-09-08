#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct SensorReadings sensorStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 50;
    readings.precipitation = 70;
    readings.humidity = 26;
    readings.windSpeedKMPH = 52;
    return readings;
}

// Custom sensor stub for rainy conditions testing
struct SensorReadings rainySensorStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 30;
    readings.precipitation = 50; // between 20 and 60
    readings.humidity = 80;
    readings.windSpeedKMPH = 30; // below 50
    return readings;
}

// Custom sensor stub for high precipitation but low wind
struct SensorReadings highPrecipLowWindStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 30;
    readings.precipitation = 70; // above 60
    readings.humidity = 85;
    readings.windSpeedKMPH = 30; // below 50
    return readings;
}

char* report(struct SensorReadings (*sensorReader)()) {
    size_t bufsize = 50;
    char* weather = (char*)malloc(bufsize);
    if (!weather) return NULL;
    struct SensorReadings readings = sensorReader();
    const char* weatherStr = "Sunny Day";
    if (readings.temperatureInC > 25) {
        if (readings.precipitation >= 20 && readings.precipitation < 60) {
            weatherStr = "Partly Cloudy";
        } else if (readings.windSpeedKMPH > 50) {
            weatherStr = "Alert, Stormy with heavy rain";
        }
    }
    snprintf(weather, bufsize, "%s", weatherStr);
    return weather;
}

void testRainy() {
    char* weather = report(rainySensorStub);
    printf("%s\n", weather);
    assert(weather && strstr(weather, "Partly Cloudy") != NULL);
    free(weather);
}

void testHighPrecipitation() {
    // This stub gives high precipitation (>60) and low wind-speed (<50)
    char* weather = report(highPrecipLowWindStub);
    // strengthen the assert to expose the bug
    // (function returns Sunny day, it should predict rain)
    assert(weather && strstr(weather, "rain") != NULL);
    free(weather);
}

int testWeatherReport() {
    printf("\nWeather report test\n");
    testRainy();
    testHighPrecipitation();
    printf("All is well (maybe!)\n");
    return 0;
}
