#include "io.h"
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

const uint32 st_io_buff_vert = 5;
const uint32 st_io_buff_hori = 5;
const uint32 st_io_buff_square
	= st_io_buff_vert * st_io_buff_hori;

st_buffer *st_io_buff_a;
st_buffer *st_io_buff_b;

st_buffer **st_io_buff_active;
st_buffer **st_io_buff_inactive;

int *st_io_test;

void
st_io_init ()
{
	// Buffer a
	st_buffer_construct (&st_io_buff_a);
	st_io_buff_a->m_rows = st_io_buff_vert;
	st_io_buff_a->m_columns = st_io_buff_hori;
	st_buffer_data_init (st_io_buff_a);
	st_buffer_data_clear (st_io_buff_a);
	st_io_buff_active = &st_io_buff_a;

	// Buffer b
	st_buffer_construct (&st_io_buff_b);
	st_io_buff_b->m_rows = st_io_buff_vert;
	st_io_buff_b->m_columns = st_io_buff_hori;
	st_buffer_data_init (st_io_buff_b);
	st_buffer_data_clear (st_io_buff_b);
	st_io_buff_inactive = &st_io_buff_b;
}

void
st_io_terminate ()
{
	// Buffer a
	st_buffer_data_terminate (st_io_buff_a);
	st_buffer_destruct (&st_io_buff_a);

	// Buffer b
	st_buffer_data_terminate (st_io_buff_b);
	st_buffer_destruct (&st_io_buff_b);
}

void
st_io_update ()
{
	for (uint32 y = 0; y < st_io_buff_vert; ++y)
	{
		for (uint32 x = 0; x < st_io_buff_hori; ++x)
		{
			st_buffer_data_set (*st_io_buff_active, y, x, 'X');
		}
	}

	int percent_complete = 0;

	while (percent_complete < 100)
	{
		printf("\rProgress: %d%%", percent_complete);
		fflush(stdout);
		++percent_complete;
		//sleep(1); // Sleep for 1 second
		usleep (50000);
	}

	// Finally print 100% and a newline
	printf("\rProgress: %d%%\n", percent_complete);

	initscr (); // Initialise ncurses
	noecho (); // Disable echoing of typed characters

	int x = 0, y = 0, count = 0;

	while (count < 1000)
	{
		mvprintw (y, x, "Hello world");
		refresh (); // Refresh the screen to display the printed text
		usleep (50000);
		++x;
		if (x > COLS) // Cursor is off the side of screen
		{
			x = 0; // Move it back to the left
			++y; // Move it down one row
		}
		if (y > LINES) // Cursor is off the bottom of the screen
		{
			y = 0; // Move it back to the top
		}
		++count;
	}

	endwin ();
}

void
st_io_draw ()
{
	for (uint32 y = 0; y < st_io_buff_vert; ++y)
	{
		for (uint32 x = 0; x < st_io_buff_hori; ++x)
		{
			char out = st_buffer_data_at (*st_io_buff_active, y, x);
			printf ("%c", out);
		}
		st_io_newline ();
	}
}

void
st_io_newline ()
{
	printf ("\n");
}
