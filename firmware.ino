#include <Keyboard.h>
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
    Keyboard.begin();
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
                        Keyboard.press(currentKeymap[i][j].keycode);
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
                        Keyboard.release(currentKeymap[i][j].keycode);
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
