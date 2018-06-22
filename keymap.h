#ifndef KEYMAP_H
#define KEYMAP_H

#include "keyboard_settings.h"
#include <stdint.h>
#include <stdbool.h>

#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof((x)[0]))

struct key
{
	uint8_t keycode;
	//`function` is executed when the key is pressed or released
	//`function`'s argument is true when pressed and false when released
	void (*function)(bool pressed);
};
struct layer
{
	uint8_t priority;
	struct key keymap[ROWS][COLUMNS];
};

extern struct key currentKeymap[ROWS][COLUMNS];

void generate_keymap(struct layer *layers[]);

#endif //KEYMAP_H