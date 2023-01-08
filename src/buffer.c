#include <stdlib.h> // malloc, free
#include <memory.h> // memset

#include "buffer.h"
#include "utils.h"

void
st_buffer_construct (st_buffer **_buffer, uint16_t _rows, uint16_t _columns)
{
	*_buffer = malloc (sizeof (st_buffer));
	(*_buffer)->m_rows = MAX (_rows, 1);
	(*_buffer)->m_columns = MAX (_columns, 1);
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
	uint16_t _row,
	uint16_t _column,
	char _val
)
{
	_row = MIN (_row, _buffer->m_rows - 1);
	_column = MIN (_column, _buffer->m_columns - 1);
	uint16_t pos = (_row * _buffer->m_columns) + _column;
	_buffer->m_data [pos] = _val;
}

char
st_buffer_data_at (
	st_buffer *_buffer,
	uint16_t _row,
	uint16_t _column
)
{
	_row = MIN (_row, _buffer->m_rows - 1);
	_column = MIN (_column, _buffer->m_columns - 1);
	uint16_t pos = (_row * _buffer->m_columns) + _column;
	return _buffer->m_data [pos];
}

uint16_t
st_buffer_get_rows (st_buffer *_buffer)
{
	return _buffer->m_rows;
}

uint16_t
st_buffer_get_columns (st_buffer *_buffer)
{
	return _buffer->m_columns;
}
