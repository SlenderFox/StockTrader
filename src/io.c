#include "io.h"
#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false
#include <string.h>

bool loaded = false;

const char clear_char = '.';

st_buffer *buffer_a, *buffer_b, **buffer_active, **buffer_inactive;

void
st_io_init (uint32_t _rows, uint32_t _columns)
{
	// Buffer a
	st_buffer_construct (&buffer_a, _rows, _columns);
	st_buffer_data_init (buffer_a);
	st_buffer_data_clear (buffer_a, clear_char);
	buffer_active = &buffer_a;

	// Buffer b
	st_buffer_construct (&buffer_b, _rows, _columns);
	st_buffer_data_init (buffer_b);
	st_buffer_data_clear (buffer_b, clear_char);
	buffer_inactive = &buffer_b;

	// Give enough room to print
	for (uint32_t i = 0; i < _rows; ++i)
	{
		printf ("\n");
	}
	fflush (stdout);

	loaded = true;
}

void
st_io_terminate ()
{
	if (!loaded)
	{
		return;
	}

	// Buffer a
	st_buffer_data_terminate (buffer_a);
	st_buffer_destruct (buffer_a);

	// Buffer b
	st_buffer_data_terminate (buffer_b);
	st_buffer_destruct (buffer_b);
}

void
st_io_draw ()
{
	if (!loaded)
	{
		return;
	}

	printf ("\e[%uF", st_io_buff_rows ());

	for (uint32_t y = 0; y < st_io_buff_rows (); ++y)
	{
		char out[st_io_buff_columns () + 1];
		out[st_io_buff_columns ()] = '\0';
		for (uint32_t x = 0; x < st_io_buff_columns (); ++x)
		{
			out[x] = st_buffer_data_at (*buffer_active, y, x);
		}
		printf ("%s\n", out);
	}
}

uint32_t
st_io_buff_rows ()
{
	return st_buffer_get_rows (buffer_a);
}

uint32_t
st_io_buff_columns ()
{
	return st_buffer_get_columns (buffer_a);
}

uint32_t
st_io_buff_square ()
{
	return st_buffer_get_rows (buffer_a) * st_buffer_get_columns (buffer_a);
}

void
st_io_buff_set (uint32_t _row, uint32_t _column, char _val)
{
	st_buffer_data_set (*buffer_active, _row, _column, _val);
}

void
st_io_buff_set_row (uint32_t _row, const char *_val)
{
	size_t len = strlen (_val);

	for (uint32_t i = 0; i < st_io_buff_columns (); ++i)
	{
		char input;
		/* If the string is shorter than the length of the line
		 * Set the rest of the line to empty characters */
		if (i >= len)
		{
			input = clear_char;
		}
		else
		{
			input = _val[i];
		}

		st_buffer_data_set (*buffer_active, _row, i, input);
	}
}
