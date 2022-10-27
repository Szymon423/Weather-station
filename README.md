# Weather station
Little project about designing portable weather station

## What do I want to achive?
My goal is to desing small weather station which is going to show weather data on E-paper screen. I want to got local weather data from builtin temperature and humidity sensor and some other data downloaded from some weather API.

## Mile stones
 * general idea about design and working properties ✅
 * find appropriate display ✅
 * decide on controll hardware ✅
 * design PCB ✅
 * wait moths for manfacturing and delievery ✅
 * assembly time
 * error fixing
 * do some coding
 * design enclousure (optional, I kinda like raw electronics)
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
   * USB to serial converter (maybe use native USB in ESP?)

### Designed PCB
One big issue which I had during clicking in easyEDA was lack of knowledge of default SPI pins. As far as I know You can change pins to which SPI is attached but I wanted to make it with default configuration. The way to check this is to dig through the documentation and find proper info (which I tried and failed) or write simple program to ESP32 board, which outputs in serial terminal information about SPI. So I ordered some ESP boards.

#### ESP32 WROOM S3 (8R8) arrived 
Becouse of it I can finally check which pins are SPI pins :) I soldered few wires to ESP32, like shown in schematic below.

<p align="center">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196614634-ae82f9af-3edd-4ff4-a6c8-97338e721600.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/196615184-c6715b09-857e-4940-aed5-b1352778c5f3.jpg">
</p>

With those connections I was able to upload some code necessary to find SPI pins - look at *SPI_pins_dectection.ino*.

<p align="center">
    <img width="500" src="https://user-images.githubusercontent.com/96399051/196534745-c78add54-8a00-44dc-b0df-beda88d84f1c.png">
</p>

Now I know that my moodule has SPI pins arranged as shown below:

<div align="center">
<table>
  <tr>
    <td>MOSI</td> <td>MISO</td> <td>SCK</td>
  </tr>
  <tr>
    <td>GPIO 35</td> <td>GPIO 37</td> <td>GPIO 36</td>
  </tr>
</table>
</div>

#### Resoult of design
<p align="center">
    <img width="700" src="https://user-images.githubusercontent.com/96399051/197221349-3f205876-662d-4a39-8b8d-d7c645a883a5.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/197221361-2ad03126-f8a9-4172-8ffd-72034494a829.png">
</p>

I never tried soldering SMD components becouse I do not own hot-air station. But becouse jlcPCB offers SMT services I want to try it. It requires little more work around to generate proper BOOM files.
#### NEVER MIND
After exporting everything (GERBER, BOM and PickAndPlace files) it turned out that SMT service will cost me arround $120... At this point I decidet to change few things. Most importantly i decided to solder all components by hand. Secondly I got rid of CP2101 USB to UART converter and put out RX and TX pins but also connected USB D+ and D- to proper pins on ESP32. At this point I reduced number of parts and my total cost (with ordering parts at LCSC) was $30 - much more affordable...

## Time for endless waiting for packages...
See you soon...

## Meanwhile i'll start playing around with the code
Check out ESP32-code folder. I want to make as easy as possible so... 
We gonna have to make few things:
 * create class for API handling:
    - send API request,
    - interpret JSON data,
 * create class for local weather data handling:
    - readings from DHT22
 * create class for E-paper display handling
    - prepare fonts,
    - prepare graphics - cloud, snow, sun, fog etc. and other necesarry icons
    - waveshare libs to use my e-ink display,
 * try to use touch sensors for stuff like:
    - force update,
    - different data,
  
