#include "firmware.h"

#ifdef DEBUG
	#include "debug.h"
#endif

void calibrate_pins()
{
	struct calibration_pin
	{
		uint8_t id;
		bool used;
	};

	struct calibration_pin pins[MATRIX_ROWS + MATRIX_COLUMNS];

	//Initialize `pins`
	for (uint8_t pin_iterator = 0; pin_iterator < MATRIX_ROWS + MATRIX_COLUMNS; pin_iterator++)
	{
		if (pin_iterator < MATRIX_ROWS)
		{
			pins[pin_iterator].id = row_pins[pin_iterator];
		}
		else
		{
			pins[pin_iterator].id = column_pins[pin_iterator - MATRIX_ROWS];
		}
		pins[pin_iterator].used = false;
	}

	//Calibrate Row Pins
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		char buffer[64];
		sprintf(buffer, "Initializing Row %d", row + 1);
		Serial.println(buffer);

		#ifdef DEBUG
			debug_prompt();
		#endif

		bool found = false;
		while (!found)
		{
			for (uint8_t possible_pin = 0; possible_pin < MATRIX_ROWS + MATRIX_COLUMNS; possible_pin++)
			{
				if (!pins[possible_pin].used)
				{
					for (uint8_t pin_iterator = 0; pin_iterator < MATRIX_ROWS + MATRIX_COLUMNS; pin_iterator++)
					{
						pinMode(pins[pin_iterator].id, INPUT);
					}
					pinMode(pins[possible_pin].id, OUTPUT);
					digitalWrite(pins[possible_pin].id, HIGH);

					for (uint8_t pin_iterator = 0; pin_iterator < MATRIX_ROWS + MATRIX_COLUMNS; pin_iterator++)
					{
						if (pin_iterator != possible_pin && digitalRead(pins[pin_iterator].id))
						{
							pins[possible_pin].used = true;
							row_pins[row] = pins[possible_pin].id;
							found = true;
							sprintf(buffer, "Setting to %hhu", pins[possible_pin].id);
							Serial.println(buffer);
						}
					}
				}
			}
		}
	}

	//Set possible pins to `INPUT`
	for (uint8_t pin_iterator = 0; pin_iterator < MATRIX_ROWS + MATRIX_COLUMNS; pin_iterator++)
	{
		pinMode(pins[pin_iterator].id, INPUT);
	}
	//Set row pins to `OUTPUT`
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		pinMode(row_pins[row], OUTPUT);
		digitalWrite(row_pins[row], LOW);
	}

	//Calibrate Column Pins
	for (uint8_t row = 0; row < MATRIX_ROWS; row++)
	{
		bool found = false;
		while (!found)
		{
			digitalWrite(row_pins[row], HIGH);
			for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
			{
				char buffer[64];
				sprintf(buffer, "Initializing Column %d", column + 1);
				Serial.println(buffer);

				#ifdef DEBUG
					debug_prompt();
				#endif

				for (uint8_t possible_pin = 0; possible_pin < MATRIX_ROWS + MATRIX_COLUMNS; possible_pin++)
				{
					if (digitalRead(pins[possible_pin].id))
					{
						column_pins[column] = pins[possible_pin].id;
						found = true;
					}
				}
			}
			digitalWrite(row_pins[row], LOW);
		}
	}
	Serial.println("Finished Calibration");
}

int main()
{
	Serial.begin(9600);

	calibrate_pins();

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
						if (!matrix[row][column].pressed)
						{
							matrix[row][column].pressed = true;
							matrix[row][column].id_when_pressed = matrix[row][column].id;
							if (matrix[row][column].id != 0x0)
							{
								Keyboard.press(matrix[row][column].id);
							}
						}
				}
				else
				{
					if (matrix[row][column].pressed)
					{
						matrix[row][column].pressed = false;
						if (matrix[row][column_pins].id_when_pressed != 0x0)
						{
							Keyboard.release(matrix[row][column].id_when_pressed);
						}
					}
				}
			}
			digitalWrite(row_pins[row], false);
		}
	}
}