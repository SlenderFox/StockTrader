#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The buffer is a linear array of characters.
 * The buffer is accessed two dimensionally.
 * Every row is contiguous in memory,
 * meaning each rows are offset by sizeof (char) * column */
typedef struct
{
	uint16_t m_rows, m_columns;
	char *m_data;
} st_buffer_t;

/** Allocate memory for the buffer struct and init values
 * @param _buff Output pointer to the buffer
 * @param _rows How many rows needed
 * @param _columns How many columns needed
 */
void
st_buff_construct (
	st_buffer_t **_buff,
	uint16_t _rows,
	uint16_t _columns
);

/** Free the memory for the buffer struct
 * @param _buff The buffer struct to be deallocated
 */
void
st_buff_destruct (st_buffer_t *_buff);

/** Allocate memory for the data stored inside the buffer struct
 * @param _buff The buffer struct whose data will be allocated
 */
void
st_buff_data_init (st_buffer_t *_buff);

/** Free the memory for the data stored inside the buffer struct
 * @param _buff The buffer struct whose data will be deallocated
 */
void
st_buff_data_terminate (st_buffer_t *_buff);

/** Set all the memory inside the data of a buffer to a given character
 * @param _buff The buffer struct to be modified
 * @param _clear What to use as the clear character
 */
void
st_buff_data_clear (st_buffer_t *_buff, char _clear);

/** Return the amount of rows in a buffer
 * @param _buff The buffer struct to be modified
 * @return [uint32_t] The amount of rows in the buffer
 */
uint16_t
st_buff_get_rows (st_buffer_t *_buff);

/** Return the amount of columns in a buffer
 * @param _buff The buffer struct to be modified
 * @return [uint32_t] The amount of columns in the buffer
 */
uint16_t
st_buff_get_columns (st_buffer_t *_buff);

/** Set a char at a specific location in a buffers data.
 * Position is clamped
 * @param _buff The buffer struct to be modified
 * @param _row The row to be accessed from
 * @param _column The column to be accessed from
 * @param _val The character to be placed at the location
 */
void
st_buff_data_set (
	st_buffer_t *_buff,
	uint16_t _row,
	uint16_t _column,
	char _val
);

/** Set a row entirely to one character
 * @param _buff The buffer struct to be modified
 * @param _row The row to be set
 * @param _val The character to set it to
 */
void
st_buff_data_row_set (
	st_buffer_t *_buff,
	uint16_t _row,
	char _val
);

/** Set an entire row to the clear character (probably space)
 * @param _buff The buffer struct to be modified
 * @param _row The row to be cleared
 * @param _clear The character used to clear with
 */
void
st_buff_data_row_clear (
	st_buffer_t *_buff,
	uint16_t _row,
	char _clear
);

/** Insert a string into the row at an offset
 * Only as many characters will be inserted as can be fit
 * @param _buff The buffer struct to be modified
 * @param _row The row to be inserted into
 * @param _offset The offset before the string is inserted
 * @param _val The string that is inserted
 */
void
st_buff_data_row_insert (
	st_buffer_t *_buff,
	uint16_t _row,
	uint16_t _offset,
	const char *_val
);

/** Get a char at a specific location in a buffers data
 * @param _buff The buffer struct to be modified
 * @param _row The row to be accessed from
 * @param _column The column to be accessed from
 * @return [char] The character at the location
 */
char
st_buff_data_get (
	st_buffer_t *_buff,
	uint16_t _row,
	uint16_t _column
);

#ifdef __cplusplus
} // extern "C"
#endif
