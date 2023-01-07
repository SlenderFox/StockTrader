#define _POSIX_C_SOURCE 200112L // For nanosleep to be used without warning

#include <stdbool.h> // bool, true, false
#include <stdio.h> // printf, fflush
#include <time.h> // timespec, nanosleep
#include <errno.h> // errno
#include <stdlib.h> // EXIT_SUCCESS
#include "io.h"
#include "company.h"

#define ROWS 8
#define COLUMNS 50
#define COMPANIES 5

/* TODO:
 * Input checking
 * Loading info into buffer
 * Redraw for linux
 * Compare replace for Windows
*/

st_company *companies[COMPANIES];

extern int
sleep(int);

bool
loading ()
{
	const uint16_t concurrents = 2;
	uint16_t percent_complete = 0;
	struct timespec ts_remaining;
	struct timespec ts_requested =
	{
		.tv_sec = 0, // 0 seconds
		.tv_nsec = 10 * 1000000 // 10 milliseconds in nanoseconds
	};

	// Initial print
	for (uint16_t i = 0; i < concurrents; ++i)
	{
		printf ("Progress: %u%%\n", percent_complete);
	}

	while (percent_complete < 100)
	{
		if (nanosleep (&ts_requested, &ts_remaining) == -1)
		{
			return false;
		}
		++percent_complete;
		// Move cursor back lines: \e[1F
		printf ("\e[%uF", concurrents);
		for (uint16_t i = 0; i < concurrents; ++i)
		{
			printf ("Progress: %u%%\n", percent_complete);
		}
		fflush (stdout);
	}

	return true;
}

void
init ()
{
	st_io_init (ROWS, COLUMNS);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_construct (&(companies[i]), "Untitled");
	}
}

void
terminate ()
{
	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_destruct (companies[i]);
	}

	st_io_terminate ();
}

int
main (int argc, char *args[])
{
	//if (!loading ())
	//{
	//	return errno;
	//}

	bool play = true;

	init ();

	while (play)
	{
		st_io_buff_set_row_from (0, 20, "StockTrader");
		st_io_buff_set_row_to (1, '=');
		st_io_buff_set (1, 0, '+');
		st_io_buff_set (1, st_io_buff_columns (), '+');
		for (uint16_t i = 0; i < COMPANIES; ++i)
		{
			st_io_buff_set_row_clear (i + 2);
			st_io_buff_set (i + 2, 0, '|');
			st_io_buff_set (i + 2, st_io_buff_columns (), '|');
		}
		st_io_buff_set_row_to (7, '=');
		st_io_buff_set (7, 0, '+');
		st_io_buff_set (7, st_io_buff_columns (), '+');

		// Outputs the contents buffer to the console
		st_io_draw ();

		sleep (1);

		for (uint16_t i = 0; i < COMPANIES; ++i)
		{
			st_io_buff_set_row_from (i + 2, 21, st_company_name_get (companies[i]));
			st_io_buff_set (i + 2, st_io_buff_columns (), '|');
		}

		// Outputs the contents buffer to the console
		st_io_draw ();

		// End game
		play = false;
	}

	terminate ();

	return EXIT_SUCCESS;
}
