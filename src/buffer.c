#include "buffer.h"
#include <stdlib.h> // malloc, free
#include <memory.h> // memset

/** Local function, returns the minimum of two values
 * @param _a The first value
 * @param _b The second value
 * @return [uint32_t] The lesser of the two values
 */
uint32_t
min (uint32_t _a, uint32_t _b)
{
	return (_a < _b) ? _a : _b;
}

/** Local function, returns the maximum of two values
 * @param _a The first value
 * @param _b The second value
 * @return [uint32_t] The greater of the two values
 */
uint32_t
max (uint32_t _a, uint32_t _b)
{
	return (_a > _b) ? _a : _b;
}

void
st_buffer_construct (st_buffer **_buffer, uint32_t _rows, uint32_t _columns)
{
	*_buffer = malloc (sizeof (st_buffer));
	(*_buffer)->m_rows = max (_rows, 1);
	(*_buffer)->m_columns = max (_columns, 1);
	(*_buffer)->m_data = NULL;
}

void
st_buffer_destruct (st_buffer *_buffer)
{
	if (_buffer->m_data != NULL)
	{
		st_buffer_data_terminate (_buffer);
	}
	free (_buffer);
}

void
st_buffer_data_init (st_buffer *_buffer)
{
	_buffer->m_data = malloc (sizeof (char) * _buffer->m_rows * _buffer->m_columns);
}

void
st_buffer_data_terminate (st_buffer *_buffer)
{
	free(_buffer->m_data);
	_buffer->m_data = NULL;
}

void
st_buffer_data_clear (st_buffer *_buffer, char _clear)
{
	memset(_buffer->m_data, _clear, sizeof (char) * _buffer->m_rows * _buffer->m_columns);
}

void
st_buffer_data_set (
	st_buffer *_buffer,
	uint32_t _row,
	uint32_t _column,
	char _val
)
{
	_row = min (_row, _buffer->m_rows - 1);
	_column = min (_column, _buffer->m_columns - 1);
	uint32_t pos = (_row * _buffer->m_columns) + _column;
	_buffer->m_data [pos] = _val;
}

char
st_buffer_data_at (
	st_buffer *_buffer,
	uint32_t _row,
	uint32_t _column
)
{
	_row = min (_row, _buffer->m_rows - 1);
	_column = min (_column, _buffer->m_columns - 1);
	uint32_t pos = (_row * _buffer->m_columns) + _column;
	return _buffer->m_data [pos];
}

uint32_t
st_buffer_get_rows (st_buffer *_buffer)
{
	return _buffer->m_rows;
}

uint32_t
st_buffer_get_columns (st_buffer *_buffer)
{
	return _buffer->m_columns;
}
