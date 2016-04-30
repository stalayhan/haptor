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
The MIT License (MIT)
Copyright © 2016 GTU

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

