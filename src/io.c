#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false
#include <string.h> // strlen
#include <assert.h> // assert
#include <stdlib.h> // system, malloc, realloc, free

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
const char clear_char = ' ';

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

	st_io_load_title ("STOCKTRADER");
	st_io_load_graph_frame ();
	st_io_load_info_day (69);
	st_io_load_info_money (10000);
	st_io_load_info_company ("Company", 0.01, 50);
	st_io_load_info_separator ();
	st_io_load_prompt ();
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

void
st_io_load_title (char *_title)
{
	st_buff_data_row_insert (*buffer_active, 0, 0, _title);
}

void
st_io_load_graph_frame ()
{
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
}

void
st_io_load_graph_data ()
{
	// TODO
}

void
st_io_load_info_day  (uint16_t _day)
{
	// Trickery to get the length of the integer
	int length = snprintf (NULL, 0, "%u", _day);
	char *value = malloc (++length);
	// Print the integer into the string, null terminating
	snprintf (value, length, "%u", _day);
	value[length - 1] = '\0';

	// Prepend the descriptor
	char *input = malloc (length + 5);
	sprintf (input, "Day: ");
	strcat (input, value);

	st_buff_data_row_insert (*buffer_active, info_offset, 0, input);

	free (value);
	free (input);
}

// TODO: Look into combining repetition into one function

void
st_io_load_info_money (double _money)
{
	// Trickery to get the length of the integer
	int length = snprintf (NULL, 0, "%.2f", _money);
	char *value = malloc (++length);
	// Print the integer into the string, null terminating
	snprintf (value, length, "%.2f", _money);
	value[length - 1] = '\0';

	// Prepend the descriptor
	char *input = malloc (length + 8);
	sprintf (input, "Money: $");
	strcat (input, value);

	st_buff_data_row_insert (*buffer_active, info_offset + 1, 0, input);

	free (value);
	free (input);
}

void
st_io_load_info_company (
	char *_name,
	double _value,
	uint32_t _owned
)
{
	int length = strlen (_name);
	char *value = malloc (length + 1);
	sprintf (value, _name);
	strcat (value, ":");
	st_buff_data_row_insert (*buffer_active, info_offset + 2, 0, value);

	// Trickery to get the length of the integer
	length = snprintf (NULL, 0, "%.2f", _value);
	value = realloc (value, ++length);
	// Print the integer into the string, null terminating
	snprintf (value, length, "%.2f", _value);
	value[length - 1] = '\0';

	// Prepend the descriptor
	char *input = malloc (length + 8);
	sprintf (input, "   $");
	strcat (input, value);
	strcat (input, " per");

	st_buff_data_row_insert (*buffer_active, info_offset + 3, 0, input);

	// Trickery to get the length of the integer
	length = snprintf (NULL, 0, "%u", _owned);
	value = realloc (value, ++length);
	// Print the integer into the string, null terminating
	snprintf (value, length, "%u", _owned);
	value[length - 1] = '\0';

	// Prepend the descriptor
	input = realloc (input, length + 9);
	sprintf (input, "   ");
	strcat (input, value);
	strcat (input, " owned");

	st_buff_data_row_insert (*buffer_active, info_offset + 4, 0, input);

	free (value);
	free (input);
}

void
st_io_load_info_separator ()
{
	st_buff_data_row_set (*buffer_active, info_offset + 5, '-');
}

void
st_io_load_prompt ()
{
	st_buff_data_row_insert (*buffer_active, info_offset + 6, 0, "> ");
}
