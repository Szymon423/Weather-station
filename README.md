# Weather station
Little project about designing portable weather station

## What do I want to achive?
My goal is to desing small weather station which is going to show weather data on E-paper screen. I want to got local weather data from builtin temperature and humidity sensor and some other data downloaded from some weather API.

## Mile stones
 * general idea about design and working properties ✅
 * find appropriate display ✅
 * decide on controll hardware ✅
 * design PCB ✅
 * wait moths for manfacturing and delievery
 * design enclousure (optional, I kinda like raw electronics)
 * do some coding
 * be happy
 
### General idea about design and working properties
As I mentioned at the beggining I want it to be portable. It means that I have to use some batteries becouse of which I have to make it possible to charge them via USB and maybe even with solar panels. becouse of need to download some data drom API, my design needs wi-fi. I want it to be quite slick desing - I have to organise everything to look cool.
 
 
### Find appropriate display

<a href="https://www.waveshare.com/catalog/product/view/id/3513/s/4.2inch-e-paper-module-c/category/37/"> link to display</a> 

<p align="center">
    <img width="800" src="https://user-images.githubusercontent.com/96399051/196177778-08e9e754-85e0-445c-af26-78eb0890aaf0.png" alt="E-paper display graphic">
</p>

### Decide on controll hardware
   * ESP32 WROOM S3 - perfect for this aplication,
   * Li-Pol 1s battery - enough capacity wor this low power aplication
   * BMS for charging and protection of 1s Li-Pol
   * Solar panel 5.5V 0.4W (optional)
   * USB-C for programming and charging
   * DHT22 for local temperature and humidity data
   * USB to serial converter

### design PCB
Currently I am stuck at this stage becouse of troubles in finding SPI pins in ESP32. Thus i ordered sample of uC and when it comes to me, I will find those pins and finish PCB so I can order it.

<p align="center">
    <img width="800" src="https://user-images.githubusercontent.com/96399051/196177778-08e9e754-85e0-445c-af26-78eb0890aaf0.png" alt="E-paper display graphic">
</p>



