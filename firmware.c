#include "firmware.h"

void change_layer(bool pressed)
{
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
		{
			if (pressed)
			{
				if (function_layer[row][column] != 0x0)
				{
					matrix[row][column].keycode = function_layer[row][column];
				}
			}
			else
			{
				matrix[row][column].keycode = main_layer[row][column];
			}
		}
	}
}

void main()
{
	//Initialize Pins
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		pinMode(row_pins[row],      OUTPUT);
		digitalWrite(row_pins[row], HIGH);
	}
	for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
	{
		pinMode(column_pins[column], INPUT_PULLUP);
		digitalWrite(column_pins[column], HIGH);
	}

	//Populate current keymap
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
		{
			matrix[row][column].pressed = false;
			matrix[row][column].keycode = main_layer[row][column];
			matrix[row][column].function = NULL;
		}
	}

	//Setup FN Key
	matrix[4][1].function = &change_layer;

	//Uncomment if the keyboard is occasionally not recognized
	//delay(2500);

	//Setup keyboard as HID device
	Keyboard.begin();

	//Main Loop
	while (true)
	{
		#ifdef DEBUG
				debug_prompt();
		#endif
		for (uint8_t row = 0; row < MATRIX_ROWS; row++)
		{
			digitalWrite(row_pins[row], LOW);
			for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
			{
				bool key_pressed = !digitalRead(column_pins[column]);
				if (key_pressed != matrix[row][column].pressed)
				{
					matrix[row][column].pressed = key_pressed;
					if (key_pressed)
					{
						if (matrix[row][column].keycode != 0x0)
						{
							Keyboard.press(matrix[row][column].keycode);
							matrix[row][column].keycode_when_pressed = matrix[row][column].keycode;
						}
						if (matrix[row][column].function != NULL)
						{
							matrix[row][column].function(true);
						}
					}
					else
					{
						if (matrix[row][column].keycode_when_pressed != 0x0)
						{
							Keyboard.release(matrix[row][column].keycode_when_pressed);
						}
						if (matrix[row][column].function != NULL)
						{
							matrix[row][column].function(false);
						}
					}
				}
			}
			digitalWrite(row_pins[row], HIGH);
		}
	}
}
