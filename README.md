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
 * assembly time ✅
 * error fixing ✅
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
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/200118391-1c545037-b72d-4435-9b2d-04e3d4fc9890.png">
    <img width="1000" src="https://user-images.githubusercontent.com/96399051/200118422-a2ce41f9-5c4a-4c0c-947a-445f1c708054.png">
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

## I wanted to see how it's going to look so..
I've made this
<p align="center">
    <img width="500" src="https://user-images.githubusercontent.com/96399051/200177085-17c673ac-e258-4a7e-a6a4-f17d2f2df1d6.gif">
</p>

## PCBs arrived, but still waiting for parts
FUCK POCZTA POLSKA ODDZIAŁ W KOMORNIKACH... but it's finally here <3

## So they look amazing...
<p align="center">
    <img width="800" src="https://user-images.githubusercontent.com/96399051/201498334-b1ec0ba2-125a-43d1-a431-b7dafbb4a589.png">
</p>
Soldering them was real pain in the ass. The 0402 elements are so small XDD. I am never going to design PCB with this small components. 

## B U T
as always I had to mess something. This time there are few things designed in wrong way. 
### BUT #1 ✅SOLVED✅
First error is This resistor.

<p align="center">
    <img width="700" src="https://user-images.githubusercontent.com/96399051/201498481-2c25a418-c743-493d-bbe4-3b5a227fba6f.png">
</p>

And this is how it's suppose to look like

<p align="center">
    <img width="700" src="https://user-images.githubusercontent.com/96399051/201498594-14afde7b-c9e3-48d2-b425-184c0fb48bd5.png">
</p>

This resistor was blocking charging current so for now I shorted it, and this part works well. I ordered 0 Ohm resistor to put there instead and I thing it's okay.

### BUT #2 ✅SOLVED✅
I ordered 10k Ohm NTC Thermistors instead of 10k Ohm resistors. They are just pullup resistors and in room tepmeratures they are just working fine, but I have to replcae them.

### BUT #3 ✅SOLVED✅
I ordered wrong value capacitors for LDO output filtering and resistors for charging current defining. But in this case it's still matter of ordering proper parts.

### BUT #4 ✅SOLVED✅
I don't know why but my LDO is eating to much current. Without anything attached to 3.3VDC there is like 5mA current consumption so it sucks AF. Ground - 3.3V resistance is like 600 Ohm... I'll have to order an LDO with lower no-load current.
After some research I've found <a href="https://www.tme.eu/pl/details/tlv1117lv33dcyt/stabilizatory-napiecia-nieregulowane-ldo/texas-instruments/"> TLV1117LV33DCYT</a> this little buddy with perfect specs:
 * low dropout voltage - at 200mA dropuot is 115mV, at 500mA it's 285mV, 
 * quiescent current at 0mA is 50μA so it's 100 times less than my previous LDO. 
It means that my circuit will last much much longer on single charge.

### BUT #5 ✅SOLVED✅
I haven't put any transistor to controll DHT22, so right now it's always powered on. This also sucks but I hope It's not going to eat to much current.
After some research I've learnt that this is quite low power demanding circuit with consumption around:
 * 1mA while measuring,
 * 40μA during standby.

### BUT #6 ✅SOLVED✅
ESP32 was also real pain in the ass to setup. I was strugling for 2 days to properly configure it in Arduino IDE. When doing it inproperly ESP32 was falling into bootloop. Luckly i found information that I am suppose to set my board as bellow:

<p align="center">
    <img width="500" src="https://user-images.githubusercontent.com/96399051/201499719-ee92b460-ac90-4714-8273-037efe10895e.PNG">
</p>

### BUT #7 ✅SOLVED✅
I have to buy bigger battery and implement deep sleep in ESP32.
I've chosen <a href="https://botland.com.pl/akumulatory-li-pol-1s-37v/15643-akumulator-li-pol-akyga-3500mah-1s-37v-zlacze-jst-bec-gniazdo-68x55x6mm-5904422324438.html">Akyga Li-Pol 3500mAh 1S battery</a> and I thing that this is quite enough. After I finish assemblu and error-fixing I'll do some measurements to check how long it can last on one charge.

### BUT #8 
Touch sensors do not want to work. Sometimes i get them working, but only sometimes. When i reset ESP32 once it works and once it doesn't. I do not know why. So I have to dig deeper to find out why...

### To do
 * try to find out why touch doesn't work
