//#include "io.h"
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char **args)
{
	char *envvar = getenv ("SHELL");
	if (envvar == NULL) envvar = "NULL\0";
	printf ("SHELL: %s\n", envvar);

	envvar = getenv ("HOME");
	if (envvar == NULL) envvar = "NULL\0";
	printf ("HOME: %s\n", envvar);

	envvar = getenv ("ROOT");
	if (envvar == NULL) envvar = "NULL\0";
	printf ("ROOT: %s\n", envvar);

	//st_io_init ();
	//st_io_draw ();
	//st_io_update ();
	//st_io_draw ();
	//st_io_terminate ();

	return 0;
}
