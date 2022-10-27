#include "weatherLOCAL.h"
#include <String.h>
#include <DHT.h>

WeatherLocal::WeatherLocal(int pin, int type) : dht(pin, type) {}

WeatherLocal::~WeatherLocal() {}

float WeatherLocal::getTemperature() {
  WeatherLocal::temperature = WeatherLocal::dht.readTemperature();
  return WeatherLocal::temperature;
}

float WeatherLocal::getHumidity() {
  WeatherLocal::humidity = WeatherLocal::dht.readHumidity();
  return WeatherLocal::humidity;
}
