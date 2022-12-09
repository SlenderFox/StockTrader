#pragma once
#include "typedefines.h"

typedef struct st_buffer
{
	char *m_data;
	uint32 m_rows, m_columns;
} st_buffer;

/** Allocate memory for the buffer struct and init values
 * @param _buf The buffer
 */
void
st_buffer_construct (st_buffer **_buf);

/** Free the memory for the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_destruct (st_buffer **_buf);

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
 */
void
st_buffer_data_clear (st_buffer *_buf);

/** Set a char at a specific location in a buffers data
 * @param _buf The buffer
 * @param _row The row
 * @param _column The column
 * @param _val The character
 */
void
st_buffer_data_set (
	st_buffer *_buf,
	uint32 _row,
	uint32 _column,
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
	uint32 _row,
	uint32 _column
);

/** Return the amount of rows in a buffer
 * @param _buf The buffer
 * @return [uint32] The amount of rows
 */
uint32
st_buffer_get_rows (st_buffer *_buf);

/** Return the amount of columns in a buffer
 * @param _buf The buffer
 * @return [uint32] The amount of columns
 */
uint32
st_buffer_get_columns (st_buffer *_buf);
