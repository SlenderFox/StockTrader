#define _POSIX_C_SOURCE 200112L // For nanosleep to be used without warning

#include "io.h"
#include <stdbool.h> // bool, true, false
#include <stdio.h> // printf, fflush
#include <time.h> // timespec, nanosleep
#include <errno.h> // errno

/* TODO:
 * Input checking
 * Loading info into buffer
 * Redraw for linux
 * Compare replace for Windows
*/

int
main (int argc, char *args[])
{
	//char *envvar = getenv ("SHELL");
	//if (envvar == NULL) envvar = "NULL\0";
	//printf ("SHELL: %s\n", envvar);

	int percent_complete = 0;
	struct timespec ts_requested =
	{
		.tv_sec = 0, // 0 seconds
		.tv_nsec = 10 * 1000000 // 10 milliseconds in nanoseconds
	};
	struct timespec ts_remaining;
	while (percent_complete < 100)
	{
		printf ("\rProgress: %d%%", percent_complete);
		fflush (stdout);
		++percent_complete;
		int ret = nanosleep (&ts_requested, &ts_remaining);
		if (ret == -1)
		{
			return errno;
		}
	}
	// Finally print 100% and a newline
	printf ("\rProgress: %d%%\n", percent_complete);

	bool play = true;
	st_io_init ();

	while (play)
	{
		// Outputs the contents buffer to the console
		st_io_draw ();

		play = false;
	}

	st_io_terminate ();

	return 0;
}
