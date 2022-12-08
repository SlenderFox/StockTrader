#include "io.h"

int
main (int argc, char **args)
{
	st_io_init ();
	st_io_draw ();
	st_io_terminate ();
	return 0;
}
