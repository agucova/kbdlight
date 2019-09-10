# kbdlight

## About
This program allows the user to change the keyboard brightness in GNU/Linux. It hasn't any extra dependecy such programs like [upower](https://upower.freedesktop.org/) (that allow to control the brightness but contains a lot other libs that sometimes you dont need).
The program adapt unix's philosophy.

## How it works
The program reads the file provided by the [kernel](https://www.kernel.org/) in ```/sys/class/leds```  
It makes the basic control: increase and decrease the brightness one by one. This depends of the value in ```max_brightness``` file

## Try it
Follows this steps:

 ```
 ./autogen.sh
 ./configure
 make
 sudo ./src/kdblight -i
 sudo ./src/kdblight -d
 ```