#define ENABLE_GxEPD2_GFX 0
#define DHTPIN 41
#define DHTTYPE DHT22
#define MAX_DISPLAY_BUFFER_SIZE 15000ul
#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))


#include <WiFi.h>
#include "time.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Adafruit_GFX.h>

#include "src/include/weatherAPI.h"
#include "src/include/weatherLocal.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////
//////                załączanie odpowiednich grafik oraz fontów                             //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>
#include <Fonts/FreeMono24pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include "fonts/Open_Sans_SemiBold_90.h"
#include "fonts/Open_Sans_SemiBold_70.h"
#include "fonts/Open_Sans_SemiBold_35.h"
#include "fonts/Open_Sans_SemiBold_25.h"

#include "graphic/background.h"
#include "graphic/moon.h"
#include "graphic/cloud_4_moon.h"
#include "graphic/sun.h"
#include "graphic/double_cloud.h"
#include "graphic/single_cloud.h"
#include "graphic/snowy_cloud.h"
#include "graphic/sun_and_cloud_SUN.h"
#include "graphic/sun_and_cloud_CLOUD.h"
#include "graphic/rainy_cloud.h"
#include "graphic/thunder_cloud_CLOUD.h"
#include "graphic/thunder_cloud_THUNDER.h"
#include "graphic/cloudy_night_MOON.h"
#include "graphic/cloudy_night_CLOUD.h"



GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT> display(GxEPD2_420c(/*CS=5*/ 38, /*DC=*/ 39, /*RST=*/ 1, /*BUSY=*/ 2));
// dane do logowania do wifi
const char* ssid = "xxxxxxxxxxxxxxxx";
const char* password = "xxxxxxxxxxxxxx";

// dane do ogarnięcia aktualnego czasu
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

// deklaracja obiektów z danymi
// WeatherLocal local(DHTPIN, DHTTYPE);
WeatherAPI api;
WeatherLocal local(DHTPIN, DHTTYPE);

int WebTemp();
int SensorTemp();
String WhatWeather();
String Wind();
String Humidity();
String DewPoint();
String Pressure1();
String Pogoda();
String MaxMin();
void PrintWeatherIcon(String opis);
int what(String that);

// zmienne odpowiadające za przechowywanie danych o bierzącej dacie oraz czasie
int year;
int month;
int day; 
int hour;
int minute;
int second;



void setup()  // Start of setup
{
  delay(5000);
  // Initiate the display
  display.init(115200);        
  display.setRotation(0);      
  display.setTextWrap(false); 
  
  // Serial 
  Serial.begin(115200);
  
  // Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wifi ");
  
  while (WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());

  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
}  




///////////////////////////////////////////////////////////////////////////////////////////////////////
//////                                    Pętla główna                                       //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void loop()  // Start of loop
{

  if (WiFi.status() == WL_CONNECTED) {
    api.update();
    int x = api.temp;
    int y = local.getTemperature();

    String wind = String(api.windSpeed);
    String humidity = String(local.getHumidity());
    String dewpoint = String(api.tempFeelsLike);
    String pressure = String(api.pressure);
    String maxmin = String(api.tempMax);
    // updateTime();
    
    Serial.print("\ntemperatura na zewnątrz: "); 
    Serial.print(x);
    Serial.print("\ntemperatura wewnątrz: ");
    Serial.print(y);

    Serial.print("\nWiatr: "); 
    Serial.print(wind);
    Serial.print("\nWilgotnosc: ");
    Serial.print(humidity);
    Serial.print("\nOdczuwalna: "); 
    Serial.print(dewpoint);
    Serial.print("\nCisnienie: ");
    Serial.print(pressure);
    Serial.print("\nTemp max: ");
    Serial.print(maxmin);
  }
  else {
    Serial.println("Connection lost");
  }

  
  delay(5000);
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
  // delay(300000);
// }





///////////////////////////////////////////////////////////////////////////////////////////////////////
//////                      dopasowanie grafiki do pogody                                    //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// void PrintWeatherIcon(String opis)
// {
//   if ((hour > 19) || (hour < 6))
//   {
//     //grafiki nocne
//     if (opis == "Fair")
//     {
//       display.drawBitmap(225, 0, gImage_cloudy_night_MOON, 144,100, GxEPD_RED);  
//       display.drawBitmap(225, 0, gImage_cloudy_night_CLOUD, 144,100, GxEPD_BLACK);
//     }
//     else if (opis == "Partly Cloudy")
//     {
//       display.drawBitmap(225, 0, gImage_cloudy_night_MOON, 144,100, GxEPD_RED);  
//       display.drawBitmap(225, 0, gImage_cloudy_night_CLOUD, 144,100, GxEPD_BLACK);
//     }
//     else if (opis == "Mostly Cloudy")
//     {
//       display.drawBitmap(225, 0, gImage_double_cloud, 144,100, GxEPD_BLACK);
//     }
//     else if (opis == "Cloudy")
//     {
//       display.drawBitmap(225, 0, gImage_cloudy_night_MOON, 144,100, GxEPD_RED);  
//       display.drawBitmap(225, 0, gImage_cloudy_night_CLOUD, 144,100, GxEPD_BLACK);
//     }
//     else if (opis == "Rain Shower" || opis == "Showers in the Vicinity")
//     {
//       display.drawBitmap(225, 0, gImage_rainy_cloud, 144,100, GxEPD_BLACK);
//     } 
//     else 
//     {
//       display.drawBitmap(225, 0, gImage_cloudy_night_MOON, 144,100, GxEPD_RED);  
//       display.drawBitmap(225, 0, gImage_cloudy_night_CLOUD, 144,100, GxEPD_BLACK);
//     }
//   }
//   else
//   {
//     //grafiki dzienne
//     if (opis == "Fair")
//     {
//       display.drawBitmap(225, 0, gImage_sun, 144,10, GxEPD_RED);
//     }
//     else if (opis == "Partly Cloudy")
//     {
//       display.drawBitmap(225, 0, gImage_sun_and_cloud_SUN, 144,100, GxEPD_RED);  
//       display.drawBitmap(225, 0, gImage_sun_and_cloud_CLOUD, 144,100, GxEPD_BLACK);
//     }
//     else if (opis == "Mostly Cloudy")
//     {
//       display.drawBitmap(225, 0, gImage_double_cloud, 144,100, GxEPD_BLACK);
//     }
//     else if (opis == "Cloudy")
//     {
//       display.drawBitmap(225, 0, gImage_single_cloud, 144,100, GxEPD_BLACK);
//     }
//      else if (opis == "Rain Shower" || opis == "Showers in the Vicinity")
//     {
//       display.drawBitmap(225, 0, gImage_rainy_cloud, 144,100, GxEPD_BLACK);
//     } 
//     else 
//     {
//       display.drawBitmap(225, 0, gImage_snowy_cloud, 144,100, GxEPD_BLACK);
//     }
//   }
//   return;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////
//////                             aktualizacja czasu                                        //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// void updateTime()
// {
//    struct tm timeinfo;
  
//   if((WiFi.status() == WL_CONNECTED))
//   {
   
//    if(!getLocalTime(&timeinfo))
//    {
//      Serial.println("Failed to obtain time");
//      return;
//    }

//    year = timeinfo.tm_year;
//    month = timeinfo.tm_mon;
//    day = timeinfo.tm_mday;
//    hour = timeinfo.tm_hour;
//    minute = timeinfo.tm_min;
//    second = timeinfo.tm_sec;
      
//   }
//   else
//   {
//     Serial.println("Connection lost");
//   }
  
//   return;
// }
