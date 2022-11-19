#pragma once

#include <Arduino.h>
#include <String.h>
#include "DHT.h"
#include <WeatherAPI.h>


class Weather {
    // class cointaining all weather data
private:
    DHT dht;
    WeatherAPI API;
public: 
    String icon;
    String tempOutside;
    String tempInside;
    String tempFeelsLike;
    String tempMax;
    String tempMin;
    String tempMaxMin;
    String humidityOutside;
    String humidityInside;
    String windSpeed;
    String pressure;
private:
    String getTemp();
    String getHumidity();
public:
    Weather(uint8_t, uint8_t);
    ~Weather();
    void update();
};

