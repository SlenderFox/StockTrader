#include "io.h"
#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false

bool loaded = false;

const uint32 buffer_vertical = 10;
const uint32 buffer_horizontal = 50;
const uint32 buffer_square = buffer_vertical * buffer_horizontal;

st_buffer *buffer_a;
st_buffer *buffer_b;

st_buffer **buffer_active;
st_buffer **buffer_inactive;

int *st_io_test;

void
st_io_init ()
{
	// Buffer a
	st_buffer_construct (&buffer_a, buffer_vertical, buffer_horizontal);
	st_buffer_data_init (buffer_a);
	st_buffer_data_clear (buffer_a);
	buffer_active = &buffer_a;

	// Buffer b
	st_buffer_construct (&buffer_b, buffer_vertical, buffer_horizontal);
	st_buffer_data_init (buffer_b);
	st_buffer_data_clear (buffer_b);
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

	for (uint32 y = 0; y < buffer_vertical; ++y)
	{
		char out[buffer_horizontal+1];
		out[buffer_horizontal] = '\0';
		for (uint32 x = 0; x < buffer_horizontal; ++x)
		{
			out[x] = st_buffer_data_at (*buffer_active, y, x);
		}
		printf ("%s\n", out);
	}
}

uint32
st_io_buff_vert ()
{
	return buffer_vertical;
}

uint32
st_io_buff_hori ()
{
	return buffer_horizontal;
}

uint32
st_io_buff_square ()
{
	return buffer_square;
}
