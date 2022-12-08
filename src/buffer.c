#include "buffer.h"
#include <stdlib.h>
#include <memory.h>

void
st_buffer_construct (st_buffer **_buf)
{
	*_buf = (st_buffer*) malloc (sizeof (st_buffer));
}

void
st_buffer_destruct (st_buffer **_buf)
{
	free (*_buf);
}

void
st_buffer_data_init (st_buffer *_buf)
{
	_buf->m_data = (char*) malloc (sizeof (char) * _buf->m_rows * _buf->m_columns);
}

void
st_buffer_data_terminate (st_buffer *_buf)
{
	free(_buf->m_data);
}

void
st_buffer_data_clear (st_buffer *_buf)
{
	memset(_buf->m_data, ' ', sizeof (char) * _buf->m_rows * _buf->m_columns);
}

void
st_buffer_data_set (
	st_buffer *_buf,
	uint64 _row,
	uint64 _column,
	char _val
)
{
	if (_row >= _buf->m_rows) _row = _buf->m_rows-1;
	if (_column >= _buf->m_columns) _column = _buf->m_columns-1;
	_buf->m_data [(_row * _buf->m_columns) + _column] = _val;
}

char
st_buffer_data_at (
	st_buffer *_buf,
	uint64 _row,
	uint64 _column
)
{
	if (_row >= _buf->m_rows) _row = _buf->m_rows-1;
	if (_column >= _buf->m_columns) _column = _buf->m_columns-1;
	return _buf->m_data [(_row * _buf->m_columns) + _column];
}

uint64
st_buffer_get_rows (st_buffer *_buf)
{
	return _buf->m_rows;
}

uint64
st_buffer_get_columns (st_buffer *_buf)
{
	return _buf->m_columns;
}
