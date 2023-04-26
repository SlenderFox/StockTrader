#include <stdlib.h> // malloc, free
#include <memory.h> // memset
#include <assert.h> // assert
#include <string.h> // strlen

#include "buffer.h"
#include "utils.h"

#define CHECK_LOADED assert (_buffer->m_data != NULL && "Buffer data not allocated");

void
st_buff_construct (
	st_buffer_t **_buffer,
	uint16_t _rows,
	uint16_t _columns
)
{
	*_buffer = malloc (sizeof (st_buffer_t));
	(*_buffer)->m_rows = MAX (_rows, 1);
	(*_buffer)->m_columns = MAX (_columns, 1);
	(*_buffer)->m_data = NULL;
}

void
st_buff_destruct (st_buffer_t *_buffer)
{
	if (_buffer->m_data != NULL)
	{
		st_buff_data_terminate (_buffer);
	}
	free (_buffer);
}

void
st_buff_data_init (st_buffer_t *_buffer)
{
	_buffer->m_data = malloc (sizeof (char) * _buffer->m_rows * _buffer->m_columns);
}

void
st_buff_data_terminate (st_buffer_t *_buffer)
{
	free (_buffer->m_data);
	_buffer->m_data = NULL;
}

void
st_buff_data_clear (st_buffer_t *_buffer, char _clear)
{
	CHECK_LOADED
	memset (_buffer->m_data, _clear, sizeof (char) * _buffer->m_rows * _buffer->m_columns);
}

uint16_t
st_buff_get_rows (st_buffer_t *_buffer)
{
	CHECK_LOADED
	return _buffer->m_rows;
}

uint16_t
st_buff_get_columns (st_buffer_t *_buffer)
{
	CHECK_LOADED
	return _buffer->m_columns;
}

void
st_buff_data_set (
	st_buffer_t *_buffer,
	uint16_t _row,
	uint16_t _column,
	char _val
)
{
	CHECK_LOADED
	_row = MIN (_row, _buffer->m_rows - 1);
	_column = MIN (_column, _buffer->m_columns - 1);
	uint16_t pos = (_row * _buffer->m_columns) + _column;
	_buffer->m_data [pos] = _val;
}

void
st_buff_data_row_set (
	st_buffer_t *_buffer,
	uint16_t _row,
	char _val
)
{
	CHECK_LOADED

	for (uint16_t i = 0; i < _buffer->m_columns; ++i)
	{
		st_buff_data_set (_buffer, _row, i, _val);
	}
}

void
st_buff_data_row_clear (
	st_buffer_t *_buffer,
	uint16_t _row,
	char _clear
)
{
	st_buff_data_row_set (_buffer, _row, _clear);
}

void
st_buff_data_row_insert (
	st_buffer_t *_buffer,
	uint16_t _row,
	uint16_t _offset,
	const char *_val
)
{
	CHECK_LOADED

	if (_offset >= _buffer->m_columns)
	{
		return;
	}

	size_t len = strlen (_val);

	for (uint16_t i = 0; i + _offset < _buffer->m_columns; ++i)
	{
		char input;

		if (i >= len)
		{
			return;
		}
		else
		{
			input = _val[i];
		}

		st_buff_data_set (_buffer, _row, i + _offset, input);
	}
}

char
st_buff_data_get (
	st_buffer_t *_buffer,
	uint16_t _row,
	uint16_t _column
)
{
	CHECK_LOADED
	_row = MIN (_row, _buffer->m_rows - 1);
	_column = MIN (_column, _buffer->m_columns - 1);
	uint16_t pos = (_row * _buffer->m_columns) + _column;
	return _buffer->m_data [pos];
}
