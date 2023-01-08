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
	st_buff_construct (&buffer_a, total_rows, total_columns);
	st_buff_data_init (buffer_a);
	st_buff_data_clear (buffer_a, clear_char);
	buffer_active = &buffer_a;

	// Buffer b
	st_buff_construct (&buffer_b, total_rows, total_columns);
	st_buff_data_init (buffer_b);
	st_buff_data_clear (buffer_b, clear_char);
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
	st_buff_data_terminate (buffer_a);
	st_buff_destruct (buffer_a);

	// Buffer b
	st_buff_data_terminate (buffer_b);
	st_buff_destruct (buffer_b);
}

void
st_io_init_graph ()
{
	assert (loaded && "io not yet loaded\n");

	// Title
	st_buff_data_row_insert (*buffer_active, 0, 0, "STOCKTRADER");

	// Graph top edge
	st_buff_data_row_set (*buffer_active, 1, '=');
	st_buff_data_set (*buffer_active, 1, 0, '+');
	st_buff_data_set (*buffer_active, 1, total_columns, '+');

	// Graph side edges
	for (uint16_t i = 0; i < graph_rows; ++i)
	{
		st_buff_data_set (*buffer_active, i + 2, 0, '|');
		st_buff_data_set (*buffer_active, i + 2, total_columns, '|');
	}

	// Graph bottom  edge
	st_buff_data_row_set (*buffer_active, info_offset - 1, '=');
	st_buff_data_set (*buffer_active, info_offset - 1, 0, '+');
	st_buff_data_set (*buffer_active, info_offset - 1, total_columns, '+');

	// Info
	for (uint16_t i = 0; i < INFO_LENGTH; ++i)
	{
		st_buff_data_row_insert (*buffer_active, info_offset + i, 0, "Info");
	}
}

void
st_io_draw ()
{
	assert (loaded && "io not yet loaded\n");

	// Move cursor back to start
	printf ("\e[%uF", total_rows + row_overflow);

	// Output the contents of the active buffer
	for (uint16_t y = 0; y < total_rows; ++y)
	{
		char out[total_columns + 1];
		out[total_columns] = '\0';
		for (uint16_t x = 0; x < total_columns; ++x)
		{
			out[x] = st_buff_data_get (*buffer_active, y, x);
		}
		printf ("%s\n", out);
	}
	fflush (stdout);
}
