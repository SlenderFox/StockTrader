#include <stdbool.h> // bool, true, false
#include <assert.h> // assert
#include <stdio.h>

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

st_company_t *companies[COMPANIES];

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

		switch (st_io_get_command ())
		{
		default:
		case st_io_command_invalid:
			st_io_print_invalid_message ();
			break;
		case st_io_command_help:
			printf ("Help\n");
			break;
		case st_io_command_endday:
			printf ("Endday\n");
			break;
		case st_io_command_gotoday:
			printf ("Gotoday\n");
			break;
		case st_io_command_select:
			printf ("Select\n");
			break;
		case st_io_command_buy:
			printf ("Buy\n");
			break;
		case st_io_command_sell:
			printf ("Sell\n");
			break;
		//default:
		//	assert ("Unexpected control path");
		}

		// TODO: Enabling looping breaks everything

		// End game
		running = false;
	}

	terminate ();

	return 0;
}
