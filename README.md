> **Note:** This is an abandoned fork of `kbdlight`, a now-extinct utility. The code is not mine.

# kbdlight 💡
# About
This command-line utility allows the user to change the brightness of a backlit keyboard in GNU/Linux.

The main advantage over alternatives like [upower](https://upower.freedesktop.org/) is the lack of unnecessary dependencies and libraries, as well as simplicity of operation. (full of UNIX goodness!)

# How it works
The program works in userspace by changing the value in the `brightness` file provided by the [kernel](https://www.kernel.org/) in `/sys/class/leds` (see [here](https://www.kernel.org/doc/Documentation/leds/leds-class.txt) for details).

For this to work, the kernel must support this type of control, the user must have appropiate permissions (in most distros, the `video` group is sufficient) and the hardware must expose the backlight to the kernel.

# Installation
## User Permissions
Add user to the `video` group:
```
sudo usermod -aG video $USER
```
Then log out and back in for the permissions to refresh.
## Packages
If you are using Arch Linux, you can install the AUR package for automatic installation [here](https://aur.archlinux.org/packages/kbdlight-git/).
If you are instead using another distro, you'll need to build and compile the program yourself, check the next section for this.

## Manual
You can build the program by yourself using make:
 ```
 git clone https://github.com/glats/kbdlight.git
 cd kbdlight
 ./autogen.sh
 ./configure
 make
 sudo make install # Install to the appropiate path.
 ```

# Usage
```
kbdlight [OPTIONS]

Options:
  -i          Increase keyboard brightness (by one)
  -d          Decrease keyboard brightness (by one)
  -c          Display current brightness
  -h          Display help.
```

## Hotkey
You can bind standard keys to increase/decrease the keyboard brightness by binding `XF86KbdBrightnessUp` to `kbdlight -i` and `XF86KbdBrightnessDown` to `kbdlight -d`.

# Notes
I wrote this because I didn't wanna use a program with a lot of dependencies to do such a simple task like control the brightness. This idea started while trying to find a minimalist program for my workstation at home, in this research I found [light](https://github.com/haikarainen/light), a simple program that allows you to control the display brightness without extra libraries. Inspired by this I tried to find something similar for keyboard backlights without success, so I decided to start learning C while writing this program. 

This is my first project in C so please be nice! Feel free to start an issue or a pull request.
