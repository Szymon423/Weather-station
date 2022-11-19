#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Adafruit_GFX.h>
#include <Weather.h>

#include "graphics/background.h"
#include "graphics/01d.h"
#include "graphics/01n_moon.h"
#include "graphics/01n_add.h"
#include "graphics/02d_cloud.h"
#include "graphics/02d_sun.h"
#include "graphics/02n_cloud.h"
#include "graphics/02n_moon.h"
#include "graphics/03d_and_03n.h"
#include "graphics/04d_and_04n.h"
#include "graphics/09d_and_09n.h"
#include "graphics/10d_and_10n_cloud.h"
#include "graphics/10d_sun.h"
#include "graphics/10n_moon.h"
#include "graphics/11d_and_11n_cloud.h"
#include "graphics/11d_and_11n_thunder.h"
#include "graphics/13d_and_13n.h"
#include "graphics/50d_and_50n_fog.h"

#include "fonts/Open_Sans_SemiBold_90.h"
#include "fonts/Open_Sans_SemiBold_70.h"
#include "fonts/Open_Sans_SemiBold_35.h"
#include "fonts/Open_Sans_SemiBold_25.h"

#define DHTPIN 41
#define DHTTYPE DHT22
#define CS 38
#define DC 39
#define RST 1
#define BUSY 2

#define ENABLE_GxEPD2_GFX 0
#define MAX_DISPLAY_BUFFER_SIZE 15000ul
#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))


// dane do logowania do wifi
// const char* ssid = "xxxxxxxxxx";
// const char* password = "xxxxxxxxxxx";

const char* ssid = "xxxxxxxxxxxxxx";
const char* password = "xxxxxxxxxxxxxxx";

// obiekty przechowujący dane o pogodzie
Weather weather(DHTPIN, DHTTYPE);

// obiekt ekranu
GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT> display(GxEPD2_420c(CS, DC, RST, BUSY));

// deklaracja funkcji
void PrintWeatherIcon(String opis);

// Start of setup
void setup() {
  // delay on start
  delay(5000);

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

  delay(3000);
  // Initiate the display
  display.init(115200);        
  display.setRotation(0);      
  display.setTextWrap(false);
  Serial.println("Display initializated");
  
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

  display.setFullWindow();  // Set full window mode, meaning is going to update the entire screen
  
  // // Here we use paged drawing, even if the processor has enough RAM for full buffer
  // // so this can be used with any supported processor board.
  // // the cost in code overhead and execution time penalty is marginal
  display.firstPage();  // Tell the graphics class to use paged drawing mode
  do
  {
    display.fillScreen(GxEPD_WHITE);  // Clear previous graphics to start over to print new things.
    display.drawBitmap(0, 0, gImage_background, 400,300, GxEPD_BLACK);  
    PrintWeatherIcon(weather.icon);
    
    display.setTextColor(GxEPD_BLACK);  // Set color for text
    display.setFont(&Open_Sans_SemiBold_35);  // Set font  Open_Sans_SemiBold_70
    display.setFont(&Open_Sans_SemiBold_90);
    
    int x = weather.tempOutside.toInt();
    if (x < 10 && x >= 0) {
      // przesunięcie o 40 punktów w prawo jeśli temperatura jest z zakresu od 0-9
      display.setCursor(52, 90);
    }
    if (x >= 10) {
      // brak przesunięcia jeśli temperatura jest z zakresu od >9
      display.setCursor(0, 90);
    }
    if (x < 0 && x > -10) {
      // brak przesunięcia jeśli temperatura jest z zakresu od -9 do 0
      display.setCursor(0, 90);
    }
    if (x < -9) {
      // przesunięcie o 40 punktów w prawo jeśli temperatura jest z zakresu < -9
      display.setCursor(0, 90);
      display.setFont(&Open_Sans_SemiBold_70);
    }
    
    
    // Set the position to start printing text (x,y)
    
    display.print(x);
    display.print("*C");
    display.setFont(&Open_Sans_SemiBold_25);
    
    display.setCursor(80, 150);
    display.print(weather.tempInside);
    display.print("*C");

    display.setCursor(80, 210);
    display.print(weather.windSpeed);
    display.print(" m/s");

    display.setCursor(80, 270);
    display.print(weather.humidityInside);
    display.print("%");

    display.setCursor(265, 150);
    display.print(weather.tempMaxMin);
    display.print("*C");

    display.setCursor(265, 210);
    display.print(weather.pressure);
    display.print(" hPa");

    display.setCursor(265, 270);
    display.print(weather.humidityOutside);
    display.print("%");
    
  }

  while (display.nextPage());  // Print everything we set previously
  // End of screen 1
  delay(300000);

}


void PrintWeatherIcon(String opis)
{
  if (opis.equals("01d")) {
    display.drawBitmap(225, 0, gImage_01d, 150,100, GxEPD_RED); 
    return;
  }
  if (opis.equals("01n")) {
    display.drawBitmap(225, 0, gImage_01n_moon, 150,100, GxEPD_RED);  
    display.drawBitmap(225, 0, gImage_01n_add, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("02d")) {
    display.drawBitmap(225, 0, gImage_02d_sun, 150,100, GxEPD_RED);  
    display.drawBitmap(225, 0, gImage_02d_cloud, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("02n")) {
    display.drawBitmap(225, 0, gImage_02n_moon, 150,100, GxEPD_RED);  
    display.drawBitmap(225, 0, gImage_02n_moon, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("03d") || opis.equals("03n")) {
    display.drawBitmap(225, 0, gImage_03d_and_03n, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("04d") || opis.equals("04n")) {
    display.drawBitmap(225, 0, gImage_04d_and_04n, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("09d") || opis.equals("09n")) {
    display.drawBitmap(225, 0, gImage_09d_and_09n, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("10d")) {
    display.drawBitmap(225, 0, gImage_10d_sun, 150,100, GxEPD_RED); 
    display.drawBitmap(225, 0, gImage_10d_and_10n_cloud, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("10n")) {
    display.drawBitmap(225, 0, gImage_10n_moon, 150,100, GxEPD_RED); 
    display.drawBitmap(225, 0, gImage_10d_and_10n_cloud, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("11d") || opis.equals("11n")) {
    display.drawBitmap(225, 0, gImage_11d_and_11n_thunder, 150,100, GxEPD_RED); 
    display.drawBitmap(225, 0, gImage_11d_and_11n_cloud, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("13d") || opis.equals("13n")) {
    display.drawBitmap(225, 0, gImage_13d_and_13n, 150,100, GxEPD_RED); 
    return;
  } 
  if (opis.equals("50d")) {
    display.drawBitmap(225, 0, gImage_10d_sun, 150,100, GxEPD_RED); 
    display.drawBitmap(225, 0, gImage_50d_and_50n_fog, 150,100, GxEPD_BLACK);
    return;
  }
  if (opis.equals("50n")) {
    display.drawBitmap(225, 0, gImage_10d_sun, 150,100, GxEPD_RED); 
    display.drawBitmap(225, 0, gImage_50d_and_50n_fog, 150,100, GxEPD_BLACK);
    return;
  }
  return;
}
