#include "game.h"
#include "io.h"
#include "company.h"

// Constants
enum {
	ROWS = 8,
	COLUMNS = 30,
	COMPANIES = 5,
	YEAR = 365
};

bool game_over = false;
bool request_exit = false;

st_company_t *companies[COMPANIES];
uint32_t day = 0;
int64_t money = 1000;

void
st_init ()
{
	st_io_init (ROWS, COLUMNS);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_construct (&(companies[i]), "Company Name That Is Really Long");
	}

	st_io_init_graph ();
}

void
st_terminate ()
{
	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_destruct (companies[i]);
	}

	st_io_terminate ();
}

void
st_update ()
{
	++day;

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_update (companies[i]);
	}

	st_io_load_info_day (day);
	st_io_load_info_company (
		companies[1]->name,
		companies[1]->value,
		companies[1]->owned_stocks
	);
	st_io_load_info_money (money);
}

bool
st_game_run ()
{
	st_init ();

	while (!game_over)
	{
		st_update();
		st_io_draw ();

		// Basic goto functionality
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
			// End game and ask to shutdown
			request_exit = true;
			game_over = true;
		}
	}

	st_terminate ();

	return request_exit;
}
