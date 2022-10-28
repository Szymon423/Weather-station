#include <WiFi.h>
#include "weatherAPI.h"
#include "weatherLocal.h"

#define DHTTYPE DHT22
#define DHTPIN 22

const char* ssid = "SSID";
const char* password = "password";

WeatherLocal local(DHTPIN, DHTTYPE);
WeatherAPI api();


void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {

}
