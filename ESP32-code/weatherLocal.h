#pragma once

#include <Arduino.h>
#include <String.h>
#include <DHT.h>

class WeatherLocal {
  private:
    float temperature;
    float humidity;
    int sensorPin;
    DHT dht;

  public:
    float getHumidity();
    float getTemperature();

  WeatherLocal(int, int);
  ~WeatherLocal();

};
