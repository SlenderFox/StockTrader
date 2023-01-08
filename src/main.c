#include <stdbool.h> // bool, true, false

#include "io.h"
#include "company.h"

enum { ROWS = 0 };
enum { COLUMNS = 0 };
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

void
print_test ()
{
	st_io_row_insert (0, 20, "StockTrader");
	st_io_row_set (1, '=');
	st_io_set (1, 0, '+');
	st_io_set (1, st_io_columns (), '+');
	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_io_row_clear (i + 2);
		st_io_set (i + 2, 0, '|');
		st_io_set (i + 2, st_io_columns (), '|');
	}
	st_io_row_set (7, '=');
	st_io_set (7, 0, '+');
	st_io_set (7, st_io_columns (), '+');

	st_io_draw ();

	sleep (1);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_io_row_insert (i + 2, 21, st_company_name_get (companies[i]));
		st_io_set (i + 2, st_io_columns (), '|');
	}

	st_io_draw ();
}

int
main (int argc, char *args[])
{
	init ();

	while (running)
	{
		//print_test ();
		st_io_init_graph ();

		st_io_draw ();

		// End game
		running = false;
	}

	terminate ();

	return 0;
}
