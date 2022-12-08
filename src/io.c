#include "io.h"
#include <stdio.h>
#include <stdlib.h>

const uint64 st_io_buffer_vertical = 5;
const uint64 st_io_buffer_horizontal = 5;
const uint64 st_io_buffer_square = st_io_buffer_vertical * st_io_buffer_horizontal;

st_buffer *st_io_buffer_a;
st_buffer *st_io_buffer_b;

st_buffer **st_io_buffer_active;
st_buffer **st_io_buffer_inactive;

int *st_io_test;

void
st_io_init ()
{
	st_buffer_construct (&st_io_buffer_a);
	st_io_buffer_a->m_rows = st_io_buffer_vertical;
	st_io_buffer_a->m_columns = st_io_buffer_horizontal;
	st_buffer_data_init (st_io_buffer_a);
	st_buffer_data_clear (st_io_buffer_a);
}

void
st_io_terminate ()
{
	st_buffer_data_terminate (st_io_buffer_a);
	st_buffer_destruct (&st_io_buffer_a);
}

void
st_io_draw ()
{
	for (uint64 y = 0; y < st_io_buffer_vertical; ++y)
	{
		for (uint64 x = 0; x < st_io_buffer_horizontal; ++x)
		{
			char out = st_buffer_data_at (st_io_buffer_a, y, x);
			printf ("%i%i%c", y, x, out);
		}
		st_io_newline ();
	}
}

void
st_io_newline ()
{
	printf ("\n");
}
