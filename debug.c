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

//Stores the state of the virtual pins
struct pin virtualPins[VIRTUAL_PIN_NUMBER] = {{INPUT, LOW}};

//Stores the state of the virtual switches
bool virtualMatrix[ROWS][COLUMNS] = {false};

//Updates virtualPins based on the state of virtualMatrix
void virtualMatrixStep()
{
	for (uint8_t i = 0; i < sizeof(virtualPins); i++)
	{
		if (virtualPins[i].mode == INPUT || virtualPins[i].mode == INPUT_PULLUP)
		{
			virtualPins[i].state = LOW;
		}
	}
	for (uint8_t i = 0; i < ROWS; i++)
	{
		if (virtualPins[row_pins[i]].state)
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
		printf(strcat(strcat(strcat(ANSI_COLOUR_RED, "ERROR: digitalWrite on INPUT pin"), ANSI_COLOUR_RESET), "\n"));
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
		printf(strcat(strcat(strcat(ANSI_COLOUR_RED, "ERROR: digitalRead on OUTPUT pin"), ANSI_COLOUR_RESET), "\n"));
	}
}