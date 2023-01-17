#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false
#include <string.h> // strlen
#include <assert.h> // assert
#include <stdlib.h> // system

#include "io.h"
#include "buffer.h"
#include "utils.h"

enum { MIN_GRAPH_ROWS = 4 };
enum { MIN_GRAPH_COLS = 20 };

// Title and vetical graph border
enum { GRAPH_PADDING_ROW = 3 };
// Side graph border
enum { GRAPH_PADDING_COL = 2 };
enum { INFO_LENGTH = 7 };

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

	info_offset = graph_rows + GRAPH_PADDING_ROW;
	total_rows = info_offset + INFO_LENGTH;
	total_columns = graph_columns + GRAPH_PADDING_COL;

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

	st_io_clear ();

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
	st_buff_data_row_insert (*buffer_active, info_offset, 0, "Day 69");
	st_buff_data_row_insert (*buffer_active, info_offset + 1, 0, "Money: $1000");
	st_buff_data_row_insert (*buffer_active, info_offset + 2, 0, "Company");
	st_buff_data_row_insert (*buffer_active, info_offset + 3, 0, "$0.01 per");
	st_buff_data_row_insert (*buffer_active, info_offset + 4, 0, "50 owned");
	st_buff_data_row_set (*buffer_active, info_offset + 5, '-');
	st_buff_data_row_insert (*buffer_active, info_offset + 6, 0, "> ");
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

void
st_io_clear ()
{
	// If no working, do _WIN32
	#ifdef __WINDOWS__
	 system ("cls");
	#else
	 system ("clear");
	#endif
}
