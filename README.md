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
</p>

#### ESP32 WROOM S3 (8R8) arrived 
Becouse of it I can finally check which pins are SPI pins :) The way I did it was simple but quite annoying. I soldered few wires to ESP32, like shown in schematic below.

<p align="center">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196614634-ae82f9af-3edd-4ff4-a6c8-97338e721600.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196615184-c6715b09-857e-4940-aed5-b1352778c5f3.jpg">
</p>

With those connections I was able to upload some code necessary to find SPI pins - look at *SPI_pins_dectection.ino*.

<p align="center">
    <img width="500" src="https://user-images.githubusercontent.com/96399051/196534745-c78add54-8a00-44dc-b0df-beda88d84f1c.png">
</p>


Now I know that my moodule has SPI pins arranged as shown below:

| MOSI          | MISO          | SCK     |
| :-----------: |:-------------:| :------:|
| GPIO 35       | GPIO 37       | GPIO 36 |



## To be continiued...
