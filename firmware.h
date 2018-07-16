#ifndef _FIRMWARE_H
#define _FIRMWARE_H

#include <stdint.h>
#include <stdbool.h>

#define MATRIX_ROWS		4
#define MATRIX_COLUMNS	12

const uint8_t row_pins[MATRIX_ROWS]			= {0, 1, 2, 3};
const uint8_t column_pins[MATRIX_COLUMNS]	= {4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16};

struct matrix_key
{
	uint8_t id;
	uint8_t id_when_pressed;
	bool pressed;
};
typedef struct matrix_key matrix_key;

matrix_key matrix[MATRIX_ROWS][MATRIX_COLUMNS] =
{
	{{0x00}, {'q'}, {'w'}, {'e'}, {'r'}, {'t'}, {'y'}, {'u'}, {'i'}, {'o'}, {'p'}, {0x00}},
	{{0x00}, {'a'}, {'s'}, {'d'}, {'f'}, {'g'}, {'h'}, {'j'}, {'k'}, {'l'}, {';'}, {'\''}},
	{{0x00}, {'z'}, {'x'}, {'c'}, {'v'}, {'b'}, {'n'}, {'m'}, {','}, {'.'}, {'/'}, {0x00}},
	{{0x00}, {0x0}, {0x0}, {0x0}, {0x0}, {' '}, {' '}, {0x0}, {0x0}, {0x0}, {0x0}, {0x00}}
};

#endif //_FIRMWARE_H