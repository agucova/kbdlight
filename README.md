# kbdlight

# About
This program allows the user to change the keyboard brightness in GNU/Linux. It hasn't any extra dependecy such programs like [upower](https://upower.freedesktop.org/) (that allow to control the brightness but contains a lot other libs that sometimes you dont need).
The program adapt unix's philosophy.

# How it works
The program reads the file provided by the [kernel](https://www.kernel.org/) in ```/sys/class/leds```  
It makes the basic control: increase and decrease the brightness one by one. This depends of the value in ```max_brightness``` file

# Installation
## Prepare user
Adding user to group video
```
sudo usermod -aG video $USER
```
logout of your session and login again

## Compiling

 ```
 git clone https://github.com/glats/kbdlight.git
 cd kbdlight
 ./autogen.sh
 ./configure
 make
 sudo make install
 ```

 ## Binding shortcut
 You can binding the binary with this shorctus:  
```XF86KbdBrightnessUp``` to run ```kbdlight -i```  
```XF86KbdBrightnessDown``` to run ```kbdlight -d```

# Notes
I wrote this because I don't wanna use a program with a lot of dependencies to do a simple task like control the brightness. 
This idea started finding minimal programs for my workstation at home. In this research I found [light](https://github.com/haikarainen/light) 
a simple program that allows you to control the display brightness without extra libraries that you will never use. With this I tried to find 
something similar for the keyboard without success. So I started to learn C I write my own program for this task.
This is my first project in C so please be nice! I'm wide open to receive improvements and receive good reviews for 