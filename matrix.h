#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdint.h>

#define MATRIX_ROWS 4
#define MATRIX_COLUMNS 12

const uint8_t matrix_row_pins[MATRIX_ROWS]			= {0, 1, 2, 3};
const uint8_t matrix_column_pins[MATRIX_COLUMNS]	= {4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16};

#endif //_MATRIX_H