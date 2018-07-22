#include "firmware.h"

#ifdef DEBUG
	#include "debug.h"
#endif

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
				if (digitalRead(column_pins[column]))
				{

				}
				else
				{

				}
			}
			digitalWrite(row_pins[row], false);
		}
	}
}