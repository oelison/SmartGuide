# SmartGuide for Oral-B (tm) brAun

Now changed to english and linux.

ToDos:

1. activate bluetooth
1. read original spi data
1. current consumption for battery to high

# compiling
```
sudo apt install sdcc
sudo apt install cmake
sudo apt install stlink-gui
sudo apt install libusb-1.0-0-dev
git clone https://github.com/onepixel0/stm8-sdcc-cmake.git
git clone https://github.com/vdudouyt/stm8flash.git
cd stm8flash
make
./stm8flash -V
```
```
../stm8flash/stm8flash -c stlinkv2 -p stm8l152 -w bin/main.ihx
../stm8flash/stm8flash -c stlinkv2 -p stm8l152c4 -w bin/main.ihx
../stm8flash/stm8flash -c stlinkv2 -p stm8l152c4 -w bin/origRom.hex
../stm8flash/stm8flash -c stlinkv2 -p stm8l152c4 -s eeprom -r bin/origDatainit.hex
```
# Debugging

## Connect a st-link
The colors from the image.
|name|color|usage|
|--|--|--|
|PIN 1|green|RST|
|PIN 2|yellow|SWIM|
|PIN 3|black|GND|
|PIN 4|orange|3v3 as 3V a Bit high but working|

![image](./images/st-link.png)

## Connect to smart-guide

![image](./images/landingPoints.png)

## License
MIT License

Copyright (c) 2024 Christian Oelschlegel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
