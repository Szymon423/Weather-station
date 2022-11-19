#include <Weather.h>

Weather::Weather(uint8_t pin, uint8_t type) : dht(pin, type) {
    Weather::dht.begin();
    Weather::icon = "";
    Weather::tempOutside = "";
    Weather::tempInside = "";
    Weather::tempFeelsLike = "";
    Weather::tempMax = "";
    Weather::tempMin = "";
    Weather::tempMaxMin = "";
    Weather::humidityOutside = "";
    Weather::humidityInside = "";
    Weather::windSpeed = "";
    Weather::pressure = "";
}

Weather::~Weather() {
}

void Weather::update() {
    Weather::API.update();
    Weather::icon = Weather::API.icon;
    Weather::tempOutside = Weather::API.temp + "*C";
    Weather::tempInside = Weather::getTemp() + "*C";
    Weather::tempFeelsLike = Weather::API.tempFeelsLike + "*C";
    Weather::tempMax = Weather::API.tempMax + "*C";
    Weather::tempMin = Weather::API.tempMin + "*C";
    Weather::tempMaxMin = Weather::API.tempMax + "/" + Weather::API.tempMin + "*C";
    Weather::humidityOutside = Weather::API.humidity + "%";
    Weather::humidityInside = Weather::getHumidity() + "%";
    Weather::windSpeed = Weather::API.windSpeed + " m/s";
    Weather::pressure = Weather::API.pressure + " hPa";
    return;
}

String Weather::getTemp() {
    float temp = Weather::dht.readTemperature();
    String toReturn {""};
    
    if (abs(temp) < 10.0) {
        toReturn = String(temp, 1);
    }
    else {
        toReturn = String(static_cast <int> (temp));
    }
    return toReturn;
}

String Weather::getHumidity() {
    float humidity = Weather::dht.readHumidity();  
    return String(static_cast <int> (humidity));
}
