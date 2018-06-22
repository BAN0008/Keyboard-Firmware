#include "keymap.h"

//Merges passed layers and assigns the result to `currentKeymap`
//The passed layers are sorted by their `priority` with 0 being highest priority

struct key currentKeymap[ROWS][COLUMNS] = {{0x0, NULL}};

void generate_keymap(struct layer *layers[])
{
	//Sort Layers(Bubble Sort)
	uint8_t swaps;
	bool done = false;
	struct layer *temp;
	while (!done)
	{
		swaps = 0;
		for (uint8_t i = 0; i < ARRAY_LENGTH(layers) - 1; i++)
		{
			if (layers[i]->priority > layers[i + 1]->priority)
			{
				temp = layers[i];
				layers[i] = layers[i + 1];
				layers[i + 1] = temp;
				swaps++;
			}
		}
		if (swaps == 0)
		{
			done = true;
		}
	}
        
	for (uint8_t i = 0; i < ROWS; i++)
	{
		for (uint8_t j = 0; j < COLUMNS; j++)
		{
			//currentKeymap[i][j] = {0x0, NULL};
			for (uint8_t k = 0; k < ARRAY_LENGTH(layers); k++)
			{
				if (layers[k]->keymap[i][j].keycode != 0x0
				|| layers[k]->keymap[i][j].function != NULL)
				{
					currentKeymap[i][j] = layers[k]->keymap[i][j];
				}
			}
		}
	}
}