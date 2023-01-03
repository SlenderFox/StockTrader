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
assert_buffer_size (st_buffer *_buf)
{
	assert(_buf->m_rows > 0 && _buf->m_columns > 0 && "Error: Buffer size is zero");
}

void
st_buffer_construct (st_buffer **_buf, uint32_t _rows, uint32_t _columns)
{
	*_buf = malloc (sizeof (st_buffer));
	(*_buf)->m_rows = _rows;
	(*_buf)->m_columns = _columns;
	(*_buf)->m_data = NULL;
}

void
st_buffer_destruct (st_buffer *_buf)
{
	if (_buf->m_data != NULL)
	{
		st_buffer_data_terminate (_buf);
	}
	free (_buf);
}

void
st_buffer_data_init (st_buffer *_buf)
{
	assert_buffer_size (_buf);
	_buf->m_data = malloc (sizeof (char) * _buf->m_rows * _buf->m_columns);
}

void
st_buffer_data_terminate (st_buffer *_buf)
{
	free(_buf->m_data);
	_buf->m_data = NULL;
}

void
st_buffer_data_clear (st_buffer *_buf, char _clear)
{
	assert_buffer_size (_buf);
	memset(_buf->m_data, _clear, sizeof (char) * _buf->m_rows * _buf->m_columns);
}

void
st_buffer_data_set (
	st_buffer *_buf,
	uint32_t _row,
	uint32_t _column,
	char _val
)
{
	assert_buffer_size (_buf);
	_row = min (_row, _buf->m_rows - 1);
	_column = min (_column, _buf->m_columns - 1);
	uint32_t pos = (_row * _buf->m_columns) + _column;
	_buf->m_data [pos] = _val;
}

char
st_buffer_data_at (
	st_buffer *_buf,
	uint32_t _row,
	uint32_t _column
)
{
	assert_buffer_size (_buf);
	_row = min (_row, _buf->m_rows - 1);
	_column = min (_column, _buf->m_columns - 1);
	uint32_t pos = (_row * _buf->m_columns) + _column;
	return _buf->m_data [pos];
}

uint32_t
st_buffer_get_rows (st_buffer *_buf)
{
	return _buf->m_rows;
}

uint32_t
st_buffer_get_columns (st_buffer *_buf)
{
	return _buf->m_columns;
}
