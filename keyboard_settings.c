#include "keyboard_settings.h"

uint8_t row_pins[ROWS] = {0, 1, 2, 3};
uint8_t column_pins[COLUMNS] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16};

struct layer normal =
{
	1, //Priority
	//struct key[ROWS][COLUMNS]
	{
		{{'7', NULL}, {'8', NULL}, {'9', NULL}},
		{{'4', NULL}, {'5', NULL}, {'6', NULL}},
		{{'1', NULL}, {'2', NULL}, {'3', NULL}}
	}
};