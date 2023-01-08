#include <stdbool.h> // bool, true, false

#include "io.h"
#include "company.h"

enum { ROWS = 8};
enum { COLUMNS = 30 };
enum { COMPANIES = 5 };

/* TODO:
 * Input checking
 * Loading info into buffer
 * Redraw for linux
 * Compare replace for Windows
*/

bool running = true;

st_company *companies[COMPANIES];

extern int
sleep(int);

void
init ()
{
	st_io_init (ROWS, COLUMNS);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_construct (&(companies[i]), "Untitled");
	}

	st_io_init_graph ();
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
	init ();

	while (running)
	{
		st_io_draw ();

		// End game
		running = false;
	}

	terminate ();

	return 0;
}
