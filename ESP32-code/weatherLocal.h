#pragma once

#include <Arduino.h>
#include <String.h>
#include <DHT.h>

class WeatherLocal {
  private:
    DHT dht;

  public:
    int getHumidity();
    int getTemperature();

  WeatherLocal(uint8_t, uint8_t);
  ~WeatherLocal();

};
