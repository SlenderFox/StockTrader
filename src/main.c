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
uint32_t day = 0;
int64_t money = 1000;

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

void
update ()
{
	++day;

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_update (companies[i]);
	}
}

int
main (int argc, char *args[])
{
	init ();

	while (running)
	{
		update();

		st_io_load_info_day (day);
		st_io_load_info_company (
			companies[1]->name,
			companies[1]->value,
			companies[1]->owned_stocks
		);
		st_io_load_info_money (money);

		st_io_draw ();

		if (st_io_get_command () == st_io_command_gotoday
			&& day < (uint32_t)st_io_get_input_value ()
		)
		{
			continue;
		}

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
