#define _POSIX_C_SOURCE 200112L // For nanosleep to be used without warning

#include "io.h"
#include <stdbool.h> // bool, true, false
#include <stdio.h> // printf, fflush
#include <time.h> // timespec, nanosleep
#include <errno.h> // errno
#include <stdlib.h> // getenv

/* TODO:
 * Input checking
 * Loading info into buffer
 * Redraw for linux
 * Compare replace for Windows
*/

void
print_shell ()
{
	// Test shell
	char *envvar = getenv ("SHELL");
	if (envvar == NULL) envvar = "NULL\0";
	printf ("SHELL: %s\n", envvar);
}

void
print_progresses (uint16_t _count, uint16_t _percent)
{
	for (uint16_t i = 0; i < _count; ++i)
	{
		printf ("Progress: %u%%\n", _percent);
	}
}

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
	print_progresses (concurrents, percent_complete);

	while (percent_complete < 100)
	{
		if (nanosleep (&ts_requested, &ts_remaining) == -1)
		{
			return false;
		}
		++percent_complete;
		// Move cursor back lines: \e[1F
		printf ("\e[%uF", concurrents);
		print_progresses (concurrents, percent_complete);
		fflush (stdout);
	}

	return true;
}

int
main (int argc, char *args[])
{
	//print_shell ();

	//if (!loading ())
	//{
	//	return errno;
	//}

	bool play = true;
	st_io_init ();
	while (play)
	{
		st_io_buff_set_row (0, "Hello world!");
		st_io_buff_set_row (1, "A long sentence.");
		st_io_buff_set_row (2, "Pneumonoultramicroscopicsilicovolcanoconiosis.");
		st_io_buff_set_row (3, "Definitely one of the lines of all time.");
		st_io_buff_set_row (4, "All of this is being read from a single buffer!");

		// Outputs the contents buffer to the console
		st_io_draw ();

		// End game
		play = false;
	}
	st_io_terminate ();

	return 0;
}
