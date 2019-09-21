# kbdlight

# About
This program allows the user to change the keyboard brightness in GNU/Linux. It hasn't any extra dependency such as [upower](https://upower.freedesktop.org/) (that allow to control the brightness, but contains a lot other libs that sometimes you dont need).
In a few words this program adapt unix's philosophy.

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

## Distros
You can install the AUR package [kbdlight-git](https://aur.archlinux.org/packages/kbdlight-git/)

## Manually

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
I wrote this because I don't wanna use a program with a lot of dependencies to do a simple task like control the brightness. This idea started trying to find a minimalist program for my workstation at home. In this research I found [light](https://github.com/haikarainen/light): a simple program that allows you to control the display brightness without extra libraries. With this I tried to find something similar for the keyboard without success. So I started to learn C I write my own program for this job. This is my first project in C so please be nice! I'm wide open to receive improvements and receive good reviews for.