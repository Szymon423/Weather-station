#include <WeatherAPI.h>
#include <String.h>
#include <HTTPClient.h>

WeatherAPI::WeatherAPI() {
  WeatherAPI::icon = "";
  WeatherAPI::windSpeed = "";
  WeatherAPI::temp = "";
  WeatherAPI::tempMax = "";
  WeatherAPI::tempMin = "";
  WeatherAPI::tempFeelsLike = "";
  WeatherAPI::pressure = "";
  WeatherAPI::humidity = "";
  WeatherAPI::APIKey = "xxxxxxxxxxxxxxxx";
  WeatherAPI::coordinatesLon = "17.0549";
  WeatherAPI::coordinatesLat = "51.1107";
  WeatherAPI::JSON = "";
  WeatherAPI::requestString = "";
}

WeatherAPI::~WeatherAPI() {
  // Serial.println("Deleting object...");
}

void WeatherAPI::getData() {
  // send API request and store it at proper file
  HTTPClient client;
  client.begin(WeatherAPI::requestString);
   
  if (client.GET() > 0) {
  WeatherAPI::JSON = client.getString();
  Serial.println(WeatherAPI::JSON);
  } 
  else {
  Serial.println("\nError on HTTP request");
  }

  return;
}

void WeatherAPI::processData() {
  // process JSON to separate
  // ready strings and ints don't need any more conversion
  WeatherAPI::icon = WeatherAPI::getValueOf("icon");
  WeatherAPI::pressure = WeatherAPI::getValueOf("pressure");
  WeatherAPI::humidity = WeatherAPI::getValueOf("humidity");

  // floats need a bit more clearing - controling precision   
  WeatherAPI::windSpeed = String(WeatherAPI::getValueOf("speed").toFloat(), 1);
  WeatherAPI::temp = String(WeatherAPI::getValueOf("temp").toFloat() - 273.0, 0); 
  WeatherAPI::tempMax = String(WeatherAPI::getValueOf("temp_max").toFloat() - 273.0, 0);
  WeatherAPI::tempMin = String(WeatherAPI::getValueOf("temp_min").toFloat() - 273.0, 0);
  WeatherAPI::tempFeelsLike = String(WeatherAPI::getValueOf("feels_like").toFloat() - 273.0, 0);
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

  WeatherAPI::requestString = "https://api.openweathermap.org/data/2.5/weather?lat=" + String(WeatherAPI::coordinatesLat); 
  WeatherAPI::requestString += "&lon=" + String(WeatherAPI::coordinatesLon) + "&appid=" + String(WeatherAPI::APIKey);
  Serial.print("\n");
  Serial.println(WeatherAPI::requestString);
  Serial.print("\n");
  return;
}

String WeatherAPI::getValueOf(String str) {
  // find start string
  int startPos = WeatherAPI::JSON.indexOf(str) + str.length() + 2;
  // find end char position basing on input type
  int finishPos = WeatherAPI::JSON.indexOf('"', startPos);
  
  if (str.equals("speed")) {
    finishPos -= 1;
  }
  if (str.equals("humidity")) {
    finishPos -= 2;
  }
  if (str.equals("pressure")) {
    finishPos -= 1;
  }
  if (str.equals("icon")) {
    startPos += 1;
    finishPos = WeatherAPI::JSON.indexOf('"', startPos + 2);
  }
    
  // return proper string
  return WeatherAPI::JSON.substring(startPos, finishPos);
}




