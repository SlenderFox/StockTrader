#include "io.h"
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char **args)
{
	char *shell = getenv ("SHELL");
	if (shell == NULL)
	{
		printf ("Shell environment variable not found\n");
	}
	else
	{
		printf ("Shell environment variable: %s\n", shell);
	}

	st_io_init ();
	st_io_draw ();
	st_io_update ();
	st_io_draw ();
	st_io_terminate ();

	return 0;
}
