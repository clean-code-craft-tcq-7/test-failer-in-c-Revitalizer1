#ifndef WEATHERREPORT_H
#define WEATHERREPORT_H

// Weather data structure
typedef struct {
    int temperature;
    int humidity;
    int precipitation;
} WeatherData;

// Interface for weather sensor
typedef struct {
    WeatherData (*read)();
} WeatherSensor;

// Function to report weather
const char* weather_report(WeatherSensor* sensor);

// Function for creating a test sensor with specific values
WeatherSensor* create_test_sensor(int temp, int humidity, int precip);

#endif // WEATHERREPORT_H