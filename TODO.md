# TODO
- Add warnings regarding the use of EEPROM.write() and EEPROM.update()
- Add pin_write() which simulates a digital pin for analog pins or just calls digitalWrite() on a digital pin
- Add pin_read() which simulates a digital pin for analog pins or just calls digitalRead() on a digital pin
- Make sure setting the pinMode to INPUT/INPUT_PULLUP with debug.h sets the state to LOW