#pragma once
#include <stdint.h>

/** The buffer is linear array of characters.
 * The buffer is accessed two dimensionally.
 * Every row is contiguous in memory,
 * meaning each rows are offset by sizeof (char) * column */
typedef struct st_buffer
{
	char *m_data;
	uint32_t m_rows, m_columns;
} st_buffer;

/** Allocate memory for the buffer struct and init values
 * @param _buf The buffer
 */
void
st_buffer_construct (st_buffer **_buf, uint32_t _rows, uint32_t _columns);

/** Free the memory for the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_destruct (st_buffer *_buf);

/** Allocate memory for the data stored inside the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_data_init (st_buffer *_buf);

/** Free the memory for the data stored inside the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_data_terminate (st_buffer *_buf);

/** Set all the memory inside the data of a buffer to a space character
 * @param _buf The buffer
 * @param _clear What to use as the clear character
 */
void
st_buffer_data_clear (st_buffer *_buf, char _clear);

/** Set a char at a specific location in a buffers data
 * @param _buf The buffer
 * @param _row The row
 * @param _column The column
 * @param _val The character
 */
void
st_buffer_data_set (
	st_buffer *_buf,
	uint32_t _row,
	uint32_t _column,
	char _val
);

/** Get a char at a specific location in a buffers data
 * @param _buf The buffer
 * @param _row The row
 * @param _column The column
 * @return [char] The character
 */
char
st_buffer_data_at (
	st_buffer *_buf,
	uint32_t _row,
	uint32_t _column
);

/** Return the amount of rows in a buffer
 * @param _buf The buffer
 * @return [uint32_t] The amount of rows
 */
uint32_t
st_buffer_get_rows (st_buffer *_buf);

/** Return the amount of columns in a buffer
 * @param _buf The buffer
 * @return [uint32_t] The amount of columns
 */
uint32_t
st_buffer_get_columns (st_buffer *_buf);
