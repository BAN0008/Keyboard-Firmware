#include "firmware.h"

#ifdef DEBUG
	#include "debug.h"
#endif //DEBUG

int main(void)
{
	//Configure pins
	for (uint8_t i = 0; i < MATRIX_ROWS; i++)
	{
		pinMode(matrix_row_pins[i], OUTPUT);
	}
	for (uint8_t i = 0; i < MATRIX_COLUMNS; i++)
	{
		pinMode(matrix_column_pins[i], INPUT_PULLUP);
	}
	Keyboard.begin();

	while (true)
	{
		for (uint8_t row = 0; row < MATRIX_ROWS; row++)
		{
			digitalWrite(matrix_row_pins[row], true);
			for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
			{
				bool key_pressed = digitalRead(column);
				if (key_pressed != matrix[row][column].pressed)
				{
					matrix[row][column].pressed = key_pressed;
					matrix[row][column].pressed_keycode = matrix[row][column].keycode;
					matrix[row][column].function(matrix[row][column]);
				}
			}
			digitalWrite(matrix_row_pins[row], false);
		}
	}
}