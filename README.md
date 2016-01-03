# haptor
Haptic Navigator

### Description
A new handheld navigation device using haptics (the sense of touch) shows potential to assist the visually impaired find their way around.

haptor provides:

* Indoor-positioning system - using triangulation or 
* Smooth sense of touch - 
* Simple control for irrlicht interface
* Pretty-print for indoor and outdoor maps.

### Screenshot

<img src='http://i.imgur.com/CB8hNzd.png?1'/>

### Hardware Specifications

* Servo Motor  (2 copy)
* Manyetometre - HMC5883L Triple Axis
* Arduino Uno R3
* Arduino Mega
* GPS Modül - GY-NEO6MV2 
* RF Modül – nRF24l01+
* Wi-Fi Modül – ESP8266
* 5Volt – Power 
* 1k, 10k, 100nF


### TO-DO
* It should be more reliable.(**Currently, under development.**)
* Indoor-positioning system should be more accurate.
* Auto detect location when user go to the outside

### Installation & Usage
* Install [Irrlicht](http://irrlicht.sourceforge.net/downloads/).
this app is tesed w/ Irrlicht SDK 1.8.3 (64-bit) on Ubuntu 14.04 **(x86_64 x86_64 x86_64 GNU/Linux)** and Windows 8.0
* Download this source code for your platform.
* If you are using Code-Blocks to run this source code under Linux - Many common problems can be solved with one of this problem steps. Project Build Options.. → → Linker Settings → Add **/usr/lib/x86_64-linux-gnu/libX11.so, /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1**

###License
<img src='https://upload.wikimedia.org/wikipedia/commons/thumb/0/0a/WTFPL_badge.svg/220px-WTFPL_badge.svg.png'/>
