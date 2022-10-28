#include "WeatherAPI.h"
#include <String.h>

WeatherAPI::WeatherAPI() {
  WeatherAPI::icon = "";
  WeatherAPI::windSpeed = 0.0;
  WeatherAPI::temp = 0.0;
  WeatherAPI::tempMax = 0.0;
  WeatherAPI::tempMin = 0.0;
  WeatherAPI::tempFeelsLike = 0.0;
  WeatherAPI::pressure = 0;
  WeatherAPI::humidity = 0;
  WeatherAPI::APIKey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  WeatherAPI::coordinatesLon = "17.0549";
  WeatherAPI::coordinatesLat = "51.1107";
  WeatherAPI::JSON = "";
  WeatherAPI::requestString = "";
}

WeatherAPI::~WeatherAPI() {
  Serial.println("Deleting object...");
}

void WeatherAPI::getData() {
  // send API request and store it at proper file

  return;
}

void WeatherAPI::processData() {
  // so the response looks like this:
  /*
  {"coord":{"lon":17.0549,"lat":51.1107},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"base":"stations",
  "main":{"temp":296.59,"feels_like":296.37,"temp_min":295.15,"temp_max":297.03,"pressure":1027,"humidity":53},"visibility":10000,
  "wind":{"speed":3.6,"deg":220},"clouds":{"all":0},"dt":1666958079,"sys":{"type":2,"id":2073402,"country":"PL","sunrise":1666935408,
  "sunset":1666971249},"timezone":7200,"id":3081368,"name":"Wrocław","cod":200}
  */
  // process JSON to separate 
  WeatherAPI::icon = WeatherAPI::getValueOf("icon");
  WeatherAPI::windSpeed = WeatherAPI::getValueOf("wind").toInt();
  WeatherAPI::pressure = WeatherAPI::getValueOf("pressure").toInt();
  WeatherAPI::humidity = WeatherAPI::getValueOf("humidity").toInt();
  WeatherAPI::temp = WeatherAPI::getValueOf("temp").toFloat(); 
  WeatherAPI::tempMax = WeatherAPI::getValueOf("temp_max").toFloat();
  WeatherAPI::tempMin = WeatherAPI::getValueOf("temp_min").toFloat();
  WeatherAPI::tempFeelsLike = WeatherAPI::getValueOf("feels_like").toFloat();
  return;
}

void WeatherAPI::update() {
  // at the very beggining we need to generate request basing on our data
  WeatherAPI::generateRequestString();
  // first step is to download data from API
  WeatherAPI::getData();
  // second step is to process data from JSON to variables
  WeatherAPI::processData();
  return;
}

void WeatherAPI::generateRequestString() {
  // example:
  // https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}

  WeatherAPI::requestString += "https://api.openweathermap.org/data/2.5/weather?lat=" + String(WeatherAPI::coordinatesLat); 
  WeatherAPI::requestString += "&lon=" + String(WeatherAPI::coordinatesLon) + "&appid=" + String(WeatherAPI::APIKey);
  return;
}

String WeatherAPI::getValueOf(String str) {
  // find start string
  int startPos = WeatherAPI::JSON.indexOf(str) + str.length() + 2;
  // find end char position basing on input type
  int finishPos = (str.equals("icon") ? WeatherAPI::JSON.indexOf('"', startPos) : WeatherAPI::JSON.indexOf('"', startPos));
  // return proper string
  return WeatherAPI::JSON.substring(startPos, finishPos);
}




