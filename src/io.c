#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false
#include <string.h> // strlen
#include <assert.h> // assert

#include "io.h"
#include "buffer.h"
#include "utils.h"

enum { MIN_GRAPH_ROWS = 5 };
enum { MIN_GRAPH_COLS = 20 };

// Graph border
enum { COL_PADDING = 2 };
// Title and graph border
enum { ROW_PADDING = 3 };
// Info length
enum { INFO_LENGTH = 5 };

bool loaded = false;
const char clear_char = '.';

uint16_t total_rows = 0, total_columns = 0;
uint16_t graph_rows = 0, graph_columns = 0;
uint16_t row_overflow = 0;

uint16_t info_offset;

st_buffer *buffer_a, *buffer_b, **buffer_active, **buffer_inactive;

void
st_io_init (uint16_t _rows, uint16_t _columns)
{
	graph_rows = MAX (_rows, MIN_GRAPH_ROWS);
	graph_columns = MAX (_columns, MIN_GRAPH_COLS);

	info_offset = graph_rows + ROW_PADDING;
	total_rows = info_offset + INFO_LENGTH;
	total_columns = graph_columns + COL_PADDING;

	// Buffer a
	st_buffer_construct (&buffer_a, total_rows, total_columns);
	st_buffer_data_init (buffer_a);
	st_buffer_data_clear (buffer_a, clear_char);
	buffer_active = &buffer_a;

	// Buffer b
	st_buffer_construct (&buffer_b, total_rows, total_columns);
	st_buffer_data_init (buffer_b);
	st_buffer_data_clear (buffer_b, clear_char);
	buffer_inactive = &buffer_b;

	// Give enough room to print
	for (uint16_t i = 0; i < total_rows; ++i)
	{
		printf ("\n");
	}
	fflush (stdout);

	loaded = true;
}

void
st_io_terminate ()
{
	assert (loaded && "io not yet loaded\n");

	// Buffer a
	st_buffer_data_terminate (buffer_a);
	st_buffer_destruct (buffer_a);

	// Buffer b
	st_buffer_data_terminate (buffer_b);
	st_buffer_destruct (buffer_b);
}

void
st_io_init_graph ()
{
	assert (loaded && "io not yet loaded\n");

	// Title
	st_io_row_insert (0, 0, "STOCKTRADER");

	// Graph top edge
	st_io_row_set (1, '=');
	st_io_set (1, 0, '+');
	st_io_set (1, st_io_columns (), '+');

	// Graph side edges
	for (uint16_t i = 0; i < graph_rows; ++i)
	{
		st_io_row_clear (i + 2);
		st_io_set (i + 2, 0, '|');
		st_io_set (i + 2, st_io_columns (), '|');
	}

	// Graph bottom  edge
	st_io_row_set (info_offset - 1, '=');
	st_io_set (info_offset - 1, 0, '+');
	st_io_set (info_offset - 1, st_io_columns (), '+');

	// Info
	for (uint16_t i = 0; i < INFO_LENGTH; ++i)
	{
		st_io_row_insert (info_offset + i, 0, "Info");
	}
}

void
st_io_draw ()
{
	assert (loaded && "io not yet loaded\n");

	// Move cursor back to start
	printf ("\e[%uF", st_io_rows () + row_overflow);

	// Output the contents of the active buffer
	for (uint16_t y = 0; y < st_io_rows (); ++y)
	{
		char out[st_io_columns () + 1];
		out[st_io_columns ()] = '\0';
		for (uint16_t x = 0; x < st_io_columns (); ++x)
		{
			out[x] = st_buffer_data_at (*buffer_active, y, x);
		}
		printf ("%s\n", out);
	}
	fflush (stdout);
}

uint16_t
st_io_rows ()
{
	return st_buffer_get_rows (buffer_a);
}

uint16_t
st_io_columns ()
{
	return st_buffer_get_columns (buffer_a);
}

uint16_t
st_io_square ()
{
	return st_buffer_get_rows (buffer_a) * st_buffer_get_columns (buffer_a);
}

void
st_io_set (uint16_t _row, uint16_t _column, char _val)
{
	assert (loaded && "io not yet loaded\n");
	st_buffer_data_set (*buffer_active, _row, _column, _val);
}

void
st_io_row_set (uint16_t _row, char _val)
{
	assert (loaded && "io not yet loaded\n");

	for (uint16_t i = 0; i < st_io_columns (); ++i)
	{
		st_buffer_data_set (*buffer_active, _row, i, _val);
	}
}

void
st_io_row_clear (uint16_t _row)
{
	st_io_row_set (_row, clear_char);
}

void
st_io_row_insert (uint16_t _row, uint16_t _offset, const char *_val)
{
	assert (loaded && "io not yet loaded\n");

	if (_offset >= st_io_columns ())
	{
		return;
	}

	size_t len = strlen (_val);

	for (uint16_t i = 0; i + _offset < st_io_columns (); ++i)
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

		st_buffer_data_set (*buffer_active, _row, i + _offset, input);
	}
}
