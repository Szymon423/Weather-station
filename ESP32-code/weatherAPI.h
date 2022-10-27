#pragma once
#include <Arduino.h>
#include <String.h>


class weatherAPI {
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
    int clouds;

  private:
    String JSON;
    String APIKey;
    String coordinatesLon;
    String coordinatesLat;

  weatherAPI();
  ~weatherAPI();

  private: 
    void getData();
    void processData();

  public:
    void update();

};
