# Keyboard Firmware
-------------------
###### Firmware for keyboards using Arduino compatible microcontrollers



### Features
- Unlimited layers changable with 
### Building
To test without a microcontroller make a symbolic link with `ln -s firmware.ino firmware.c` and build with `cc *.c -D DEBUG -o firmware` then run with `./firmware`

To run on a microcontroller open `firmware.ino` in the Arduino IDE and press upload.
