#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdint.h>
#include <stdbool.h>

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

void pinMode()
{

}
void digitalWrite(uint8_t pin, bool state)
{

}
bool digitalRead(uint8_t pin)
{

}

void Keyboard_begin()
{

}
void Keyboard_press(uint8_t keycode)
{

}
void Keyboard_release(uint8_t keycode)
{

}

const struct
{
	void (*begin)(void);
	void (*press)(uint8_t keycode);
	void (*release)(uint8_t keycode);
} Keyboard = {&Keyboard_begin, &Keyboard_press, &Keyboard_release};

#endif //_DEBUG_H