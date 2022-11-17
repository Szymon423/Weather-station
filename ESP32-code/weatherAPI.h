#pragma once

#include <Arduino.h>
#include <String.h>


class WeatherAPI {
  // class responsible for recieving weather data from API

  public:
    String icon;
    int windSpeed;
    int temp;
    int tempMax;
    int tempMin;
    int tempFeelsLike;
    int pressure;
    int humidity;

  private:
    String JSON;
    String APIKey;
    String coordinatesLon;
    String coordinatesLat;
    String requestString;

  

  private: 
    void getData();
    void processData();
    void generateRequestString();
    String getValueOf(String);

  public:
    void update();
    WeatherAPI();
    ~WeatherAPI();

};
