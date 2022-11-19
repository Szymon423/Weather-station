#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Adafruit_GFX.h>
#include <Weather.h>

#define DHTPIN 41
#define DHTTYPE DHT22

#define ENABLE_GxEPD2_GFX 0
#define MAX_DISPLAY_BUFFER_SIZE 15000ul
#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))


// dane do logowania do wifi
const char* ssid = "xxxxxxxxx";
const char* password = "xxxxxxxxxx";

// obiekty przechowujący dane o pogodzie
Weather weather(DHTPIN, DHTTYPE);

// Start of setup
void setup() {
  // Serial port
  Serial.begin(115200);
  
  // Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wifi ");
  
  while (WiFi.status()!= WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  
}  


// Start of loop
void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    // aktualizacja danych na temat pogody
    weather.update();

    Serial.print("\nTemperatura na zewnątrz: ");  Serial.print(weather.tempOutside);
    Serial.print("\nTemperatura wewnątrz: ");     Serial.print(weather.tempInside);
    Serial.print("\nTemperatura odczuwalna: ");   Serial.print(weather.tempFeelsLike);
    Serial.print("\nWiatr: ");                    Serial.print(weather.windSpeed);
    Serial.print("\nCisnienie: ");                Serial.print(weather.pressure);
    Serial.print("\nTemp Max: ");                 Serial.print(weather.tempMax);
    Serial.print("\nTemp Min: ");                 Serial.print(weather.tempMin);
    Serial.print("\nTemp Max/Min: ");             Serial.print(weather.tempMaxMin);
    Serial.print("\nWilgotność wewnątrz: ");      Serial.print(weather.humidityInside);
    Serial.print("\nWilgotność na zewnątrz: ");   Serial.print(weather.humidityOutside);
    Serial.print("\nIkona do pokazania: ");       Serial.print(weather.icon);
    Serial.print("\n\n");
  }
  else {
    Serial.println("Connection lost");
  }

  // display.setFullWindow();  // Set full window mode, meaning is going to update the entire screen
  
  // // Here we use paged drawing, even if the processor has enough RAM for full buffer
  // // so this can be used with any supported processor board.
  // // the cost in code overhead and execution time penalty is marginal
  // display.firstPage();  // Tell the graphics class to use paged drawing mode
  // do
  // {
  //   display.fillScreen(GxEPD_WHITE);  // Clear previous graphics to start over to print new things.
  //   display.drawBitmap(0, 0, gImage_background, 400,300, GxEPD_BLACK);  
  //   // PrintWeatherIcon(opis);
    
  //   display.setTextColor(GxEPD_BLACK);  // Set color for text
  //   display.setFont(&Open_Sans_SemiBold_35);  // Set font  Open_Sans_SemiBold_70
  //   display.setFont(&Open_Sans_SemiBold_90);
    
  //   if (x<10 && x>=0)  // przesunięcie o 40 punktów w prawo jeśli temperatura jest z zakresu od 0-9
  //   {
  //     display.setCursor(52, 90);
  //   }
  //   if (x>=10)        // brak przesunięcia jeśli temperatura jest z zakresu od >9
  //   {
  //     display.setCursor(0, 90);
  //   }
  //   if (x<0 && x>-10) // brak przesunięcia jeśli temperatura jest z zakresu od -9 do 0
  //   {
  //     display.setCursor(0, 90);
  //   }
  //   if (x < -9)        // przesunięcie o 40 punktów w prawo jeśli temperatura jest z zakresu < -9
  //   {
  //     display.setCursor(0, 90);
  //     display.setFont(&Open_Sans_SemiBold_70);
  //   }
    
    
  //     // Set the position to start printing text (x,y)
    
  //   display.print(x);
  //   display.print("*C");
  //   display.setFont(&Open_Sans_SemiBold_25);
    
  //   display.setCursor(80, 150);
  //   display.print(y);
  //   display.print("*C");

  //   display.setCursor(80, 210);
  //   display.print(wind);

  //   display.setCursor(80, 270);
  //   display.print(humidity);

  //   display.setCursor(265, 150);
  //   display.print(maxmin);

  //   display.setCursor(265, 210);
  //   display.print(pressure);

  //   display.setCursor(265, 270);
  //   display.print(dewpoint);
  //   display.print("*C");
    
  // }

  // while (display.nextPage());  // Print everything we set previously
  // // End of screen 1
  delay(300000);

}
