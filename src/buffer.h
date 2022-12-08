#pragma once
#include "typedefines.h"

typedef struct st_buffer
{
	char *m_data;
	uint64 m_rows, m_columns;
} st_buffer;

void
st_buffer_clear (st_buffer *_buf);

void
st_buffer_set (
	st_buffer *_buf,
	uint64 _row,
	uint64 _column,
	char _val
);

char
st_buffer_at (
	st_buffer *_buf,
	uint64 _row,
	uint64 _column
);

uint64
st_buffer_get_rows (st_buffer *_buf);

uint64
st_buffer_get_columns (st_buffer *_buf);
