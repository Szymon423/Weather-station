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
    <img width="700" src="https://user-images.githubusercontent.com/96399051/196188731-9ab27082-e6db-49f7-9c36-b119f6a931ea.png">
</p>

### Decide on controll hardware
   * ESP32 WROOM S3 - perfect for this aplication,
   * Li-Pol 1s battery - enough capacity wor this low power aplication
   * BMS for charging and protection of 1s Li-Pol
   * Solar panel 5.5V 0.4W (optional)
   * USB-C for programming and charging
   * DHT22 for local temperature and humidity data
   * USB to serial converter

### Designed PCB
Currently I am stuck at this stage becouse of troubles in finding SPI pins in ESP32. Thus i ordered sample of uC and when it comes to me, I will find those pins and finish PCB so I can order it.

<p align="center">
    <img width="700" src="https://user-images.githubusercontent.com/96399051/196184159-a23547b7-e0d4-463d-8653-d4d45a4162a4.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196183280-c72d3c10-4ad7-40ee-a218-40e4544c3f27.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196182075-ed64cc35-3423-40c2-9f1f-27ffc8650ccb.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196182224-ddec7c48-9f9d-4ff3-b8a5-33375a903772.png">
</p>

#### ESP32 WROOM S3 (8R8) arrived 
Becouse of i I can finally check which pins are SPI pins :) The way I did it was simple but quite annoying. I soldered few wires to ESP32, like shown in schematic below.
