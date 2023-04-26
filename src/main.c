#include <stdbool.h> // bool, true, false
#include <assert.h> // assert
#include <stdio.h> // printf

#include "io.h"
#include "company.h"

// Constants
enum {
	ROWS = 8,
	COLUMNS = 30,
	COMPANIES = 5,
	YEAR = 365
};

bool running = true;

st_company_t *companies[COMPANIES];
uint16_t day = 0;

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

		st_io_process_input ();

		// Temporary exit command
		if (st_io_get_command () == st_io_command_exit)
		{
			// End game
			running = false;
		}
	}

	terminate ();

	printf ("Bye\n");
	return 0;
}
