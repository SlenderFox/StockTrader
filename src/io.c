#include "io.h"
#include <stdlib.h>
#include <stdio.h>

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
	st_io_test = (int*)malloc(sizeof(int));
	*st_io_test = 5;
	//st_io_buffer_a = (st_buffer*)malloc(sizeof(st_buffer) * st_io_buffer_square);
	//st_buffer_clear(st_io_buffer_a);
}

void
st_io_terminate ()
{
	free(st_io_test);
	//free(st_io_buffer_a);
}

void
st_io_draw ()
{
	printf("Fuck you = %i\n", *st_io_test);
	//for (uint64 y = 0; y < st_io_buffer_vertical; ++y)
	//{
	//	for (uint64 x = 0; x < st_io_buffer_horizontal; ++x)
	//	{
	//		char out = st_buffer_at(st_io_buffer_a, 1, 2);
	//		printf("%i%i%c", 1, 2, out);
	//	}
	//}
}
