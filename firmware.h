#ifndef _FIRMWARE_H
#define _FIRMWARE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "matrix.h"

struct key
{
	uint8_t	keycode;						//keycode sent to the computer when the key is pressed/released
	bool	pressed;						//Whether the key is being pressed or not
	uint8_t	pressed_keycode;				//Value of `keycode` during the last press
	void	(*function)(struct key self);	//Function that is called when the key is pressed/released
};

struct key matrix[MATRIX_ROWS][MATRIX_COLUMNS] = 
{
	{{0x00, 0, 0, 0}, {'q', 0, 0, 0}, {'w', 0, 0, 0}, {'e', 0, 0, 0}, {'r', 0, 0, 0}, {'t', 0, 0, 0}, {'y', 0, 0, 0}, {'u', 0, 0, 0}, {'i', 0, 0, 0}, {'o', 0, 0, 0}, {'p', 0, 0, 0}, {0x00, 0, 0, 0}},
	{{0x00, 0, 0, 0}, {'a', 0, 0, 0}, {'s', 0, 0, 0}, {'d', 0, 0, 0}, {'f', 0, 0, 0}, {'g', 0, 0, 0}, {'h', 0, 0, 0}, {'j', 0, 0, 0}, {'k', 0, 0, 0}, {'l', 0, 0, 0}, {';', 0, 0, 0}, {'\'', 0, 0, 0}},
	{{0x00, 0, 0, 0}, {'z', 0, 0, 0}, {'x', 0, 0, 0}, {'c', 0, 0, 0}, {'v', 0, 0, 0}, {'b', 0, 0, 0}, {'n', 0, 0, 0}, {'m', 0, 0, 0}, {',', 0, 0, 0}, {'.', 0, 0, 0}, {'/', 0, 0, 0}, {0x00, 0, 0, 0}},
	{{0x00, 0, 0, 0}, {0x0, 0, 0, 0}, {0x0, 0, 0, 0}, {0x0, 0, 0, 0}, {0x0, 0, 0, 0}, {' ', 0, 0, 0}, {' ', 0, 0, 0}, {0x0, 0, 0, 0}, {0x0, 0, 0, 0}, {0x0, 0, 0, 0}, {0x0, 0, 0, 0}, {0x00, 0, 0, 0}}
};

#endif //_FIRMWARE_H