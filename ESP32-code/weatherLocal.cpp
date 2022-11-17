#include "include/weatherLocal.h"
#include <String.h>
#include <DHT.h>

WeatherLocal::WeatherLocal(uint8_t pin, uint8_t type) : dht(pin, type) {
  WeatherLocal::dht.begin();
}

WeatherLocal::~WeatherLocal() {}

int WeatherLocal::getTemperature() {
  return static_cast <int> (WeatherLocal::dht.readTemperature());
}

int WeatherLocal::getHumidity() {
  return static_cast <int> (WeatherLocal::dht.readHumidity());
}
