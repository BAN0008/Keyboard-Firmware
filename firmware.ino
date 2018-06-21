#ifndef DEBUG
	#include <Keyboard.h>
#else
	#include <stdio.h>
	#include "debug.h"
#endif
//#include "keymap.h"
#include "keyboard_settings.h"

//State of all keys
//true = pressed, false = not pressed
bool keyStates[ROWS][COLUMNS] = {false};

void setup()
{
	//Configure Pins
	for (uint8_t i = 0; i < ROWS; i++)
	{
		pinMode(row_pins[i], OUTPUT);
	}
	for (uint8_t i = 0; i < COLUMNS; i++)
	{
		pinMode(column_pins[i], INPUT_PULLUP);
	}

	#ifdef STARTUP_DELAY
		delay(STARTUP_DELAY);
	#endif

	#ifndef DEBUG
		Keyboard.begin();
	#else
		Keyboard_begin();
	#endif
}

void loop()
{
	for (uint8_t i = 0; i < ROWS; i++)
	{
		digitalWrite(row_pins[i], HIGH);
		for (uint8_t j = 0; j < COLUMNS; j++)
		{
			bool currentKeyState = digitalRead(column_pins[j]);
			if (currentKeyState != keyStates[i][j])
			{
				keyStates[i][j] = currentKeyState;
				if (currentKeyState)
				{
					if (currentKeymap[i][j].keycode != 0x0)
					{
						#ifndef DEBUG
							Keyboard.press(currentKeymap[i][j].keycode);
						#else
							Keyboard_press(currentKeymap[i][j].keycode);
						#endif
					}
					if (currentKeymap[i][j].function != NULL)
					{
						currentKeymap[i][j].function(true);
					}
				}
				else
				{
					if (currentKeymap[i][j].keycode != 0x0)
					{
						#ifndef DEBUG
							Keyboard.release(currentKeymap[i][j].keycode);
						#else
							Keyboard_release(currentKeymap[i][j].keycode);
						#endif
					}
					if (currentKeymap[i][j].function != NULL)
					{
						currentKeymap[i][j].function(false);
					}
				}
			}
		}
		digitalWrite(row_pins[i], LOW);
	}
}

#ifdef DEBUG
int main()
{
	bool virtualMatrix[ROWS][COLUMNS] = {false};

	setup();
	char command;
	uint8_t row;
	uint8_t column;
	while (true)
	{
		printf("\n\np/r[Press/Release]: ");
		scanf(" %c",&command);
		printf("Row: ");
		scanf(" %u",&row);
		printf("Column: ");
		scanf(" %u",&column);
		virtualMatrix[row][column] = (command == 'p');
		loop();
	}
	return 0;
}
#endif