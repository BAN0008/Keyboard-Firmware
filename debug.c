#include "debug.h"
#include <stdio.h>
#include <string.h>

void pinMode(uint8_t pin, uint8_t mode) {}

void Keyboard_begin()
{
	printf("Keyboard Begin\n");
}

void Keyboard_press(uint8_t keycode)
{
	printf("%c Pressed\n", keycode);
}

void Keyboard_release(uint8_t keycode)
{
	printf("%c Released\n", keycode);
}

struct pin virtualPins[VIRTUAL_PIN_NUMBER] = {{INPUT, LOW}};

void digitalWrite(uint8_t pin, bool signal)
{
	if (virtualPins[pin].mode == OUTPUT)
	{
		virtualPins[pin].state = signal;
	}
	else
	{
		printf(strcat(strcat(strcat(ANSI_COLOUR_RED, "ERROR: digitalWrite on INPUT pin"), ANSI_COLOUR_RESET), "\n"));
	}
}

bool digitalRead(uint8_t pin)
{

}