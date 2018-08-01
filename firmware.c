#include "firmware.h"

#ifdef DEBUG
	#include "debug.h"
#endif

void pin_write(uint8_t pin, bool state)
{
	digitalWrite(pin, state);
}
bool pin_read(uint8_t pin)
{
	return digitalRead(pin);
}

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
		sprintf(buffer, "Initializing %d", row + 1);
		Serial.println(buffer);
		for (uint8_t possible_pin = 0; possible_pin < MATRIX_ROWS + MATRIX_COLUMNS; possible_pin++)
		{
			if (!pins[possible_pin].used)
			{
				for (uint8_t pin_iterator1 = 0; pin_iterator1 < MATRIX_ROWS + MATRIX_COLUMNS; pin_iterator1++)
				{
					pinMode(pins[pin_iterator1].id, INPUT);
				}
				pinMode(pins[possible_pin].id, OUTPUT);
				pin_write(pins[possible_pin].id, HIGH);

				while (!pins[possible_pin].used)
				{
					#ifdef DEBUG
						debug_prompt();
					#endif
					for (uint8_t pin_iterator2 = 0; pin_iterator2 < MATRIX_ROWS + MATRIX_COLUMNS; pin_iterator2++)
					{
						if (possible_pin != pin_iterator2)
						{
							if (pin_read(pins[pin_iterator2].id))
							{
								pins[possible_pin].used = true;
								row_pins[row] = pins[possible_pin].id;
							}
						}
					}
				}
			}
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
			pin_write(row_pins[row], true);
			for (uint8_t column = 0; column < MATRIX_COLUMNS; column++)
			{
				if (pin_read(column_pins[column]))
				{

				}
				else
				{

				}
			}
			pin_write(row_pins[row], false);
		}
	}
}