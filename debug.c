#include "debug.h"
#include <stdio.h>
#include <signal.h>

void pinMode(uint8_t pin, uint8_t mode)
{
	if (pin < VIRTUAL_PIN_NUMBER)
	{
		virtualPins[pin].mode = mode;
	}
	else
	{
		printf("\x1b[31mERROR: pinMode on NON EXISTING PIN pin\x1b[0m\n");
	}
}

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

//Stores the state of the virtual pins
struct pin virtualPins[VIRTUAL_PIN_NUMBER] = {{INPUT, LOW}};

//Stores the state of the virtual switches
bool virtualMatrix[ROWS][COLUMNS] = {false};

//Updates virtualPins based on the state of virtualMatrix
void virtualMatrixStep()
{
	for (uint8_t i = 0; i < ARRAY_LENGTH(virtualPins); i++)
	{
		if (virtualPins[i].mode == INPUT || virtualPins[i].mode == INPUT_PULLUP)
		{
			virtualPins[i].state = LOW;
		}
	}
	for (uint8_t i = 0; i < ROWS; i++)
	{
		if (virtualPins[row_pins[i]].state == HIGH)
		{
			for (uint8_t j = 0; j < COLUMNS; j++)
			{
				if (virtualMatrix[i][j])
				{
					virtualPins[column_pins[j]].state = HIGH;
				}
			}
		}
	}
}

void digitalWrite(uint8_t pin, bool signal)
{
	if (virtualPins[pin].mode == OUTPUT)
	{
		virtualPins[pin].state = signal;
	}
	else
	{
		printf("\x1b[31mERROR: digitalWrite on INPUT pin\x1b[0m\n");
		raise(SIGINT);
	}
}

bool digitalRead(uint8_t pin)
{
	virtualMatrixStep();
	if (virtualPins[pin].mode == INPUT | virtualPins[pin].mode == INPUT_PULLUP)
	{
		return virtualPins[pin].state;
	}
	else
	{
		printf("\x1b[31mERROR: digitalRead on OUTPUT pin\x1b[0m\n");
		raise(SIGINT);
	}
}