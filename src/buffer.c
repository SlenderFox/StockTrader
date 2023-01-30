#include <stdlib.h> // malloc, free
#include <memory.h> // memset
#include <assert.h> // assert
#include <string.h> // strlen

#include "buffer.h"
#include "utils.h"

void
st_buff_construct (st_buffer_t **_buff, uint16_t _rows, uint16_t _columns)
{
	*_buff = malloc (sizeof (st_buffer_t));
	(*_buff)->m_rows = MAX (_rows, 1);
	(*_buff)->m_columns = MAX (_columns, 1);
	(*_buff)->m_data = NULL;
}

void
st_buff_destruct (st_buffer_t *_buff)
{
	if (_buff->m_data != NULL)
	{
		st_buff_data_terminate (_buff);
	}
	free (_buff);
}

void
st_buff_data_init (st_buffer_t *_buff)
{
	_buff->m_data = malloc (sizeof (char) * _buff->m_rows * _buff->m_columns);
}

void
st_buff_data_terminate (st_buffer_t *_buff)
{
	free (_buff->m_data);
	_buff->m_data = NULL;
}

void
st_buff_data_clear (st_buffer_t *_buff, char _clear)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");
	memset (_buff->m_data, _clear, sizeof (char) * _buff->m_rows * _buff->m_columns);
}

uint16_t
st_buff_get_rows (st_buffer_t *_buff)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");
	return _buff->m_rows;
}

uint16_t
st_buff_get_columns (st_buffer_t *_buff)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");
	return _buff->m_columns;
}

void
st_buff_data_set (
	st_buffer_t *_buff,
	uint16_t _row,
	uint16_t _column,
	char _val
)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");
	_row = MIN (_row, _buff->m_rows - 1);
	_column = MIN (_column, _buff->m_columns - 1);
	uint16_t pos = (_row * _buff->m_columns) + _column;
	_buff->m_data [pos] = _val;
}

void
st_buff_data_row_set (
	st_buffer_t *_buff,
	uint16_t _row,
	char _val
)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");

	for (uint16_t i = 0; i < _buff->m_columns; ++i)
	{
		st_buff_data_set (_buff, _row, i, _val);
	}
}

void
st_buff_data_row_clear (
	st_buffer_t *_buff,
	uint16_t _row,
	char _clear
)
{
	st_buff_data_row_set (_buff, _row, _clear);
}

void
st_buff_data_row_insert (
	st_buffer_t *_buff,
	uint16_t _row,
	uint16_t _offset,
	const char *_val
)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");

	if (_offset >= _buff->m_columns)
	{
		return;
	}

	size_t len = strlen (_val);

	for (uint16_t i = 0; i + _offset < _buff->m_columns; ++i)
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

		st_buff_data_set (_buff, _row, i + _offset, input);
	}
}

char
st_buff_data_get (
	st_buffer_t *_buff,
	uint16_t _row,
	uint16_t _column
)
{
	assert (_buff->m_data != NULL && "Buffer data not allocated");
	_row = MIN (_row, _buff->m_rows - 1);
	_column = MIN (_column, _buff->m_columns - 1);
	uint16_t pos = (_row * _buff->m_columns) + _column;
	return _buff->m_data [pos];
}
