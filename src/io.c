#include "io.h"
#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false
#include <string.h>

bool loaded = false;

const uint32_t buffer_vertical = 5, buffer_horizontal = 50;
const uint32_t buffer_square = buffer_vertical * buffer_horizontal;
const char clear_char = '.';

st_buffer *buffer_a, *buffer_b, **buffer_active, **buffer_inactive;

void
st_io_init ()
{
	// Buffer a
	st_buffer_construct (&buffer_a, buffer_vertical, buffer_horizontal);
	st_buffer_data_init (buffer_a);
	st_buffer_data_clear (buffer_a, clear_char);
	buffer_active = &buffer_a;

	// Buffer b
	st_buffer_construct (&buffer_b, buffer_vertical, buffer_horizontal);
	st_buffer_data_init (buffer_b);
	st_buffer_data_clear (buffer_b, clear_char);
	buffer_inactive = &buffer_b;

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
	st_buffer_destruct (&buffer_a);

	// Buffer b
	st_buffer_data_terminate (buffer_b);
	st_buffer_destruct (&buffer_b);
}

void
st_io_draw ()
{
	if (!loaded)
	{
		return;
	}

	for (uint32_t y = 0; y < buffer_vertical; ++y)
	{
		char out[buffer_horizontal+1];
		out[buffer_horizontal] = '\0';
		for (uint32_t x = 0; x < buffer_horizontal; ++x)
		{
			out[x] = st_buffer_data_at (*buffer_active, y, x);
		}
		printf ("%s\n", out);
	}
}

uint32_t
st_io_buff_vert ()
{
	return buffer_vertical;
}

uint32_t
st_io_buff_hori ()
{
	return buffer_horizontal;
}

uint32_t
st_io_buff_square ()
{
	return buffer_square;
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

	for (uint32_t i = 0; i < buffer_horizontal; ++i)
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
