#ifndef KEYBOARD_SETTINGS_H
#define KEYBOARD_SETTINGS_H

//Define matrix
#define ROWS 4
#define COLUMNS 12

#include <stdint.h>
#include <stdlib.h>
#include "keymap.h"

extern uint8_t row_pins[ROWS];
extern uint8_t column_pins[COLUMNS];

//Uncomment the below line if the keyboard is occasionally not recognized
//#define STARTUP_DELAY 2500

//Define Layers Here
//Example Layer
extern struct layer normal;

#endif //KEYBOARD_SETTINGS_H