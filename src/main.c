//#include "io.h"
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char **args)
{
	int res = system ("clear");
	printf ("Result: %i\n", res);

	char *shell = getenv ("SHELL");
	if (shell != NULL)
	{
		printf ("SHELL: %s\n", shell);
	}

	char *comspec = getenv ("ComSpec");
	if (comspec != NULL)
	{
		printf ("ComSpec: %s\n", comspec);
	}

	// Try using system () and checking the result

	//st_io_init ();
	//st_io_draw ();
	//st_io_update ();
	//st_io_draw ();
	//st_io_terminate ();

	return 0;
}
