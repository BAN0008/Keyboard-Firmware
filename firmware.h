#ifndef _FIRMWARE_H
#define _FIRMWARE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define MATRIX_ROWS	5
#define MATRIX_COLUMNS	17

const uint8_t row_pins[MATRIX_ROWS]       = {0, 1, 2, 3, 4};
const uint8_t column_pins[MATRIX_COLUMNS] = {5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22};

#ifdef DEBUG
	#include "debug.h"
#endif

struct matrix_key
{
	uint8_t keycode;
	uint8_t keycode_when_pressed;
	void    (*function)(bool pressed);
	bool 	pressed;
};
typedef struct matrix_key matrix_key;

matrix_key matrix[MATRIX_ROWS][MATRIX_COLUMNS];

const uint8_t main_layer[MATRIX_ROWS][MATRIX_COLUMNS] =
{
	{'`',            '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '=', KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP},
	{KEY_TAB,        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', KEY_DELETE, KEY_END, KEY_PAGE_DOWN},
	{KEY_CAPS_LOCK,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', KEY_RETURN, 0x0, 0x0, 0x0},
	{KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KEY_RIGHT_SHIFT, 0x0, 0x0, 0x0, 0x0},
	{KEY_LEFT_CTRL, 0x0 /*FN Key setup in firmware.c*/, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 0x0, 0x0, 0x0, 0x0, 0x0}
};

const uint8_t function_layer[MATRIX_ROWS][MATRIX_COLUMNS] =
{
	{KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 0x0, 0x0, 0x0},
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x0/*FN Key*/, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
};

#endif //_FIRMWARE_H
