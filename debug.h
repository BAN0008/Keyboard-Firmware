#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include <stdbool.h>
#include "keyboard_settings.h"

#define VIRTUAL_PIN_NUMBER 27

#define ANSI_COLOUR_RED     "\x1b[31m"
#define ANSI_COLOUR_RESET   "\x1b[0m"
#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

void pinMode(uint8_t pin, uint8_t mode);

void Keyboard_begin();
void Keyboard_press(uint8_t keycode);
void Keyboard_release(uint8_t keycode);

struct pin
{
	uint8_t mode;
	bool state;
};

extern struct pin virtualPins[VIRTUAL_PIN_NUMBER];
extern bool virtualMatrix[ROWS][COLUMNS];

void virtualMatrixStep();

void digitalWrite(uint8_t pin, bool signal);
bool digitalRead(uint8_t pin);

#endif //DEBUG_H