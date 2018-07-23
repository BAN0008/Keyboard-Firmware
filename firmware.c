#include "firmware.h"

int main()
{
	//Initialize Pins
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		pinMode(row_pins[row], OUTPUT);
	}
	for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
	{
		pinMode(column_pins[column], INPUT);
	}

	//Populate current keymap
	matrix_key matrix[MATRIX_ROWS][MATRIX_COLUMNS];
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
		{
			matrix[row][column].keycode = main_layer[row][column];
		}
	}

	//Main Loop
	while (true)
	{
		#ifdef DEBUG
				debug_prompt();
		#endif
		for (uint8_t row = 0; row < MATRIX_ROWS; row++)
		{
			digitalWrite(row_pins[row], true);
			for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
			{
				bool key_pressed = digitalRead(column_pins[column]);
				if (key_pressed != matrix[row][column].pressed)
				{
					matrix[row][column].pressed = key_pressed;
					if (key_pressed)
					{
						Keyboard.press(matrix[row][column].keycode);
						matrix[row][column].keycode_when_pressed = matrix[row][column].keycode;
					}
					else
					{
						Keyboard.release(matrix[row][column].keycode_when_pressed);
					}
				}
			}
			digitalWrite(row_pins[row], false);
		}
	}
}