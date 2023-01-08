#pragma once
#include <stdint.h>

/** Constrcuts all the buffers
 * @param _rows How many rows the graph will have
 * @param _columns How many columns the graph will have
 */
void
st_io_init (uint16_t _rows, uint16_t _columns);

/** Decontructs all the buffers */
void
st_io_terminate ();

void
st_io_init_graph ();

/** Outputs the contents of the buffer to the standard output */
void
st_io_draw ();

/** Value sourced from buffer a
 * @return [uint16_t] The amount of rows in the buffers
 */
uint16_t
st_io_rows ();

/** Value sourced from buffer a
 * @return [uint16_t] The amount of columns in the buffers
 */
uint16_t
st_io_columns ();

/** Value sourced from buffer a
 * @return [uint16_t] The product of the rows and columns in the buffers
 */
uint16_t
st_io_square ();

/** Set a position in the active buffer to the given character
 * @param _row The vertical position from the top left, will be clamped
 * @param _column How horizontal position from the top left, will be clamped
 * @param _val The character to be set
 */
void
st_io_set (
	uint16_t _row,
	uint16_t _column,
	char _val
);

/** Set a row entirely to one character
 * @param _row The row to be set
 * @param _val The character to set it to
 */
void
st_io_row_set (uint16_t _row, char _val);

/** Set an entire row to the clear character (probably space)
 * @param _row The row to be cleared
 */
void
st_io_row_clear (uint16_t _row);

/** Insert a string into the row at an offset
 * Only as many characters will be inserted as can be fit
 * @param _row The row to be inserted into
 * @param _offset The offset before the string is inserted
 * @param _val The string that is inserted
 */
void
st_io_row_insert (
	uint16_t _row,
	uint16_t _offset,
	const char *_val
);
