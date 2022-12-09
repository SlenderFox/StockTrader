#pragma once
#include "typedefines.h"

typedef struct
{
	char *m_data;
	uint32 m_rows, m_columns;
} st_buffer;

/** Allocates memory for the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_construct (st_buffer **_buf);

/** Frees the memory for the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_destruct (st_buffer **_buf);

/** Allocates memory for the data stored inside the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_data_init (st_buffer *_buf);

/** Frees the memory for the data stored inside the buffer struct
 * @param _buf The buffer
 */
void
st_buffer_data_terminate (st_buffer *_buf);

/** Sets all the memory inside the data of a buffer to a space character
 * @param _buf The buffer
 */
void
st_buffer_data_clear (st_buffer *_buf);

/** Sets a char at a specific location in a buffers data
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

/** Gets a char at a specific location in a buffers data
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

/** Returns the amount of rows in a buffer
 * @param _buf The buffer
 * @return [uint32] The amount of rows
 */
uint32
st_buffer_get_rows (st_buffer *_buf);

/** Returns the amount of columns in a buffer
 * @param _buf The buffer
 * @return [uint32] The amount of columns
 */
uint32
st_buffer_get_columns (st_buffer *_buf);
