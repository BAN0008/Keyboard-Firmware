# Keyboard Firmware
 Firmware for keyboards using Arduino compatible microcontrollers

**This project is still early in development and not all listed features are present**

## Features
- Unlimited layers
- Software debouncing
- Macros

## Building
To test without a microcontroller make a symbolic link with `ln -s firmware.ino firmware.c` and build with `cc *.c -D DEBUG -o firmware` then run with `./firmware`

To run on a microcontroller open `firmware.ino` in the Arduino IDE and press upload.

## Configuration
### Matrix
Define the number of rows and columns in your matrix
```c
//keyboard_settings.h
#define ROWS 3
#define COLUMNS 3
```
Specify pins used for rows and columns
```c
//keyboard_settings.c
const uint8_t row_pins[ROWS] = {0, 1, 2};
const uint8_t column_pins[COLUMNS] = {4, 5, 6};
```
### Layers
There must be at least one layer for the keyboard to function.
|Tag               |Description|
| ---------------- | --------- |
|[LAYER_NAME]      |Name of the layer(can't contain spaces)|
|[LAYER_PRIORITY]  |Number above 0. Makes the layer override other enabled layers with a higher priority value|
|[KEY_KEYCODE]     |Keycode sent when the key is pressed. See [Keycodes](#keycodes)(Use `0x0` for keys that shouldn't directly send anything)|
|[KEY_FUNCTION]    |Address of function called when key pressed/released. Use `NULL` for normal keys(used for macros and layer changing)    |

Layers are defined in the following format 
```c
//firmware.ino
/*
void setup()
{
	...
	struct layer *temp[1] = {&[LAYER_NAME]};
	generate_keymap(temp);
}
*/
//Example
void setup()
{
	...
	struct layer *temp[1] = {&layer_numpad};
	generate_keymap(temp);
}
```
```c
//keyboard_settings.h
//extern struct layer [LAYER_NAME];
//Example
extern struct layer layer_numpad;
```
```c
//keyboard_settings.c
/*
struct layer [LAYER_NAME] = 
{
	[LAYER_PRIORITY],
	{   //             COL 1                  COL 2    ...
		{{[KEY_KEYCODE], [KEY_FUNCTION]}, {'Q', NULL}, ...}, //ROW 1
		{{'A', NULL}, {'S', NULL}, ...}                      //ROW 2
	}                                                        //...
*/
//Example
struct layer layer_numpad =
{
	1,
	{
		{{'7', NULL}, {'8', NULL}, {'9', NULL}},
		{{'4', NULL}, {'5', NULL}, {'6', NULL}},
		{{'1', NULL}, {'2', NULL}, {'3', NULL}}
	}
};
```
### Keycodes
You can use single quotation marks to specify a character code for a printable character. eg, `'a'`
Below is a list of constants for other keys
```c
KEY_LEFT_CTRL
KEY_LEFT_SHIFT
KEY_LEFT_ALT
KEY_LEFT_GUI
KEY_RIGHT_CTRL
KEY_RIGHT_SHIFT
KEY_RIGHT_ALT
KEY_RIGHT_GUI
KEY_UP_ARROW
KEY_DOWN_ARROW
KEY_LEFT_ARROW
KEY_RIGHT_ARROW
KEY_BACKSPACE
KEY_TAB
KEY_RETURN
KEY_ESC
KEY_INSERT
KEY_DELETE
KEY_PAGE_UP
KEY_PAGE_DOWN
KEY_HOME
KEY_END
KEY_CAPS_LOCK
KEY_F1
KEY_F2
KEY_F3
KEY_F4
KEY_F5
KEY_F6
KEY_F7
KEY_F8
KEY_F9
KEY_F10
KEY_F11
KEY_F12
```
