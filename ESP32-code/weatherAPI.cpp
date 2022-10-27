#include "weatherAPI.h"
#include <String.h>

weatherAPI::weatherAPI() {
  weatherAPI::icon = "";
  weatherAPI::windSpeed = 0.0;
  weatherAPI::temp = 0.0;
  weatherAPI::tempMax = 0.0;
  weatherAPI::tempMin = 0.0;
  weatherAPI::tempFeelsLike = 0.0;
  weatherAPI::pressure = 0;
  weatherAPI::humidity = 0;
  weatherAPI::clouds = 0;
  weatherAPI::APIKey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  weatherAPI::coordinatesLon = "17.0549";
  weatherAPI::coordinatesLat = "51.1107";
  weatherAPI::JSON = "";
}

weatherAPI::~weatherAPI() {
  Serial.println("Deleting object...");
}

void weatherAPI::getData() {
  // send API request and store it at proper file
}

void weatherAPI::processData() {
  // process JSON to separate 
}

void weatherAPI::update(){
  // first step is to download data from API
  weatherAPI::getData();
  // second step is to process data from JSON to variables
  weatherAPI::processData();
}





