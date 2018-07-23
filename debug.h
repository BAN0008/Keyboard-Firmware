#ifndef _DEBUG_H
#define _DEBUG_H

#include "firmware.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define PIN_COUNT 24

//Define Pin States
#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

//Define keycodes
#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT  0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL  0x84
#define KEY_RIGHT_SHIFT 0x85
#define KEY_RIGHT_ALT   0x86
#define KEY_RIGHT_GUI   0x87
#define KEY_UP_ARROW    0xDA
#define KEY_DOWN_ARROW  0xD9
#define KEY_LEFT_ARROW  0xD8
#define KEY_RIGHT_ARROW 0xD7
#define KEY_BACKSPACE   0xB2
#define KEY_TAB         0xB3
#define KEY_RETURN      0xB0
#define KEY_ESC         0xB1
#define KEY_INSERT      0xD1
#define KEY_DELETE      0xD4
#define KEY_PAGE_UP     0xD3
#define KEY_PAGE_DOWN   0xD6
#define KEY_HOME        0xD2
#define KEY_END         0xD5
#define KEY_CAPS_LOCK   0xC1
#define KEY_F1          0xC2
#define KEY_F2          0xC3
#define KEY_F3          0xC4
#define KEY_F4          0xC5
#define KEY_F5          0xC6
#define KEY_F6          0xC7
#define KEY_F7          0xC8
#define KEY_F8          0xC9
#define KEY_F9          0xCA
#define KEY_F10         0xCB
#define KEY_F11         0xCC
#define KEY_F12         0xCD

struct virtual_pin
{
	uint8_t mode;
	bool    state;
};

struct virtual_pin virtual_pins[PIN_COUNT];
bool   virtual_matrix[MATRIX_ROWS][MATRIX_COLUMNS] = {false};
bool   keyboard_began = false;

void initialize_virtual_pins()
{
	static bool initialized = false;
	if (!initialized)
	{
		printf("\x1b[32mINFO: Initializing Virtual Pins\x1b[0m\n");
		for (uint8_t i = 0; i < PIN_COUNT; i++)
		{
			virtual_pins[i].mode = INPUT;
			virtual_pins[i].state = LOW;
		}
		initialized = true;
	}
}

void simulate_matrix()
{
	for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
	{
		virtual_pins[column_pins[column]].state = false;
	}
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		if (virtual_pins[row_pins[row]].state)
		{
			for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
			{
				virtual_pins[column_pins[column]].state = virtual_matrix[row][column];
			}
		}
	}
}

void delay(int milliseconds)
{
	usleep(milliseconds * 1000);
}

void pinMode(uint8_t pin, uint8_t mode)
{
	const char* modes[3] = {"OUTPUT", "INPUT", "INPUT_PULLUP"};
	initialize_virtual_pins();
	if (pin < PIN_COUNT)
	{
		printf("\x1b[32mINFO: Setting mode of pin \x1b[34m`%hhu`\x1b[32m to \x1b[34m`%s`\x1b[32m\x1b[0m\n", pin, modes[mode]);
		virtual_pins[pin].mode = mode;
	}
	else
	{
		printf("\x1b[31mERROR: Cannot set the mode of non existing pin \x1b[34m`%hhu`\x1b[0m\n", pin);
	}
}
void digitalWrite(uint8_t pin, bool state)
{
	initialize_virtual_pins();
	if (pin < PIN_COUNT)
	{
		if (virtual_pins[pin].mode == OUTPUT)
		{
			virtual_pins[pin].state = state;
		}
		else
		{
			printf("\x1b[31mERROR: Cannot set the state of input pin \x1b[34m`%hhu`\x1b[0m\n", pin);
		}
	}
	else
	{
		printf("\x1b[31mERROR: Cannot set the state of non existing pin \x1b[34m`%hhu`\x1b[0m\n", pin);
	}
}
bool digitalRead(uint8_t pin)
{
	initialize_virtual_pins();
	simulate_matrix();
	if (pin < PIN_COUNT)
	{
		if (virtual_pins[pin].mode == INPUT || virtual_pins[pin].mode == INPUT_PULLUP)
		{
			return virtual_pins[pin].state;
		}
		else
		{
			printf("\x1b[31mERROR: Cannot read the state of output pin \x1b[34m`%hhu`\x1b[0m\n", pin);
		}
	}
	else
	{
		printf("\x1b[31mERROR: Cannot read the state of non existing pin \x1b[34m`%hhu`\x1b[0m\n", pin);
	}
	return LOW;
}

void Keyboard_begin()
{
	keyboard_began = true;
	printf("\x1b[32mINFO: \x1b[34m`Keyboard.begin()`\x1b[32m called\x1b[0m\n");
}
void Keyboard_press(uint8_t keycode)
{
	if (!keyboard_began)
	{
		printf("\x1b[1;33mWARNING: \x1b[34m`Keyboard.press()`\x1b[1;33m called before \x1b[34m`Keyboard.begin()`\x1b[0m\n");
	}
	printf("\x1b[35mPressing key \x1b[34m0x%x/%c\x1b[0m\n", keycode, keycode);
}
void Keyboard_release(uint8_t keycode)
{
	if (!keyboard_began)
	{
		printf("\x1b[1;33mWARNING: \x1b[34m`Keyboard.release()`\x1b[1;33m called before \x1b[34m`Keyboard.begin()`\x1b[0m\n");
	}
	printf("\x1b[35mReleasing key \x1b[34m0x%x/%c\x1b[0m\n", keycode, keycode);
}

void debug_prompt()
{
	char command;
	bool done = false;
	uint8_t row, column;
	while (!done)
	{
		printf("\x1b[0mCommand > \x1b[35m");
		//scanf(" %c", &command);
		//scanf(" %c %hhu %hhu", &command, &row, &column);
		char *line = malloc(16);
		fgets(line, 16, stdin);
		line = strtok(line, "\n");
		uint8_t args = 1;
		for (uint8_t i = 0; i < 16; i++)
		{
			if (line[i] == ' ')
			{
				args++;
			}
		}
		command = strtok(line, " ")[0];
		if (args == 3)
		{
			row = atoi(strtok(NULL, " "));
			column = atoi(strtok(NULL, " "));
		}

		switch (command)
		{
			case 'h':
				printf("h - Print list of commands\nc - Continue\np <ROW> <COLUMN> - Press a key\nr <ROW> <COLUMN> - Release a key\nq - Quit\n\n");
				break;
			case 'q':
				exit(0);
				break;
			case 'c':
				done = true;
				break;
			case 'p':
				/*
				printf("\x1b[0m    Row > \x1b[35m");
				scanf(" %hhu", &row);
				printf("\x1b[0m Column > \x1b[35m");
				scanf(" %hhu", &column);
				*/
				if (row <= MATRIX_ROWS && column <= MATRIX_COLUMNS && row > 0 && column > 0)
				{
					virtual_matrix[row - 1][column - 1] = true;
				}
				else
				{
					printf("\x1b[31mERROR: Key out of bounds. Matrix size is %dx%d\n", MATRIX_ROWS, MATRIX_COLUMNS);
				}
				break;
			case 'r':
				/*
				printf("\x1b[0m    Row > \x1b[35m");
				scanf(" %hhu", &row);
				printf("\x1b[0m Column > \x1b[35m");
				scanf(" %hhu", &column);
				*/
				if (row <= MATRIX_ROWS && column <= MATRIX_COLUMNS && row > 0 && column > 0)
				{
					virtual_matrix[row - 1][column - 1] = false;
				}
				else
				{
					printf("\x1b[31mERROR: Key out of bounds. Matrix size is %dx%d\n", MATRIX_ROWS, MATRIX_COLUMNS);
				}
				break;
		}
	}
	printf("\x1b[0m");
}

const struct
{
	void (*begin)(void);
	void (*press)(uint8_t keycode);
	void (*release)(uint8_t keycode);
} Keyboard = {&Keyboard_begin, &Keyboard_press, &Keyboard_release};

#endif //_DEBUG_H