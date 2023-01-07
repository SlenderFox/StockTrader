#include "buffer.h"
#include <stdlib.h> // malloc, free
#include <memory.h> // memset
#include <assert.h> // assert

/* Local function */
uint32_t
min (uint32_t _a, uint32_t _b)
{
	return (_a < _b) ? _a : _b;
}

void
assert_buffer_size (st_buffer *_buffer)
{
	assert(_buffer->m_rows > 0 && _buffer->m_columns > 0 && "Error: Buffer size is zero");
}

void
st_buffer_construct (st_buffer **_buffer, uint32_t _rows, uint32_t _columns)
{
	*_buffer = malloc (sizeof (st_buffer));
	(*_buffer)->m_rows = _rows;
	(*_buffer)->m_columns = _columns;
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
	assert_buffer_size (_buffer);
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
	assert_buffer_size (_buffer);
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
	assert_buffer_size (_buffer);
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
	assert_buffer_size (_buffer);
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
