#pragma once

#include <Arduino.h>
#include <String.h>


class WeatherAPI {
  // class responsible for recieving weather data from API

  public:
    String icon;
    float windSpeed;
    float temp;
    float tempMax;
    float tempMin;
    float tempFeelsLike;
    int pressure;
    int humidity;

  private:
    String JSON;
    String APIKey;
    String coordinatesLon;
    String coordinatesLat;
    String requestString;

  WeatherAPI();
  ~WeatherAPI();

  private: 
    void getData();
    void processData();
    void generateRequestString();
    String getValueOf(String);

  public:
    void update();

};
