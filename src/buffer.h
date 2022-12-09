#pragma once
#include "typedefines.h"

typedef struct
{
	char *m_data;
	uint32 m_rows, m_columns;
} st_buffer;

void
st_buffer_construct (st_buffer **_buf);

void
st_buffer_destruct (st_buffer **_buf);

void
st_buffer_data_init (st_buffer *_buf);

void
st_buffer_data_terminate (st_buffer *_buf);

void
st_buffer_data_clear (st_buffer *_buf);

void
st_buffer_data_set (
	st_buffer *_buf,
	uint32 _row,
	uint32 _column,
	char _val
);

char
st_buffer_data_at (
	st_buffer *_buf,
	uint32 _row,
	uint32 _column
);

uint32
st_buffer_get_rows (st_buffer *_buf);

uint32
st_buffer_get_columns (st_buffer *_buf);