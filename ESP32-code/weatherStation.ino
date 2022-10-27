#include "weatherAPI.h"
#include "weatherLocal.h"

#define DHTTYPE DHT22
#define DHTPIN 22

WeatherLocal local(DHTPIN, DHTTYPE);
WeatherAPI api();


void setup() {
  Serial.begin(9600);
  
}

void loop() {

}
