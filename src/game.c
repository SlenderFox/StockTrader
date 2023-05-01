#include <assert.h> // assert
#include <stdlib.h> // malloc, free
#include <stdio.h> // snprintf

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
bool going_to_day = false;

st_company_t *companies[COMPANIES];
uint8_t selected_company = 0;
uint32_t day = 0;
int64_t money = 1000;

void
st_game_init ()
{
	st_io_init (ROWS, COLUMNS);

	char *name = malloc (ST_COMPANY_NAME_MAX);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		snprintf (name, COLUMNS + 3, "Company Number %u", i + 1);
		st_company_construct (&(companies[i]), name);
	}

	free (name);

	st_io_init_graph ();
}

void
st_game_terminate ()
{
	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_destruct (companies[i]);
	}

	st_io_terminate ();
}

void
st_game_over_screen ()
{

}

void
st_game_attempt_buy ()
{
	if (money < companies[selected_company]->value * st_io_get_input_value ())
	{
		return;
	}

	money -= companies[selected_company]->value * st_io_get_input_value ();
	companies[selected_company]->owned_stocks += st_io_get_input_value ();
}

void
st_game_attempt_sell ()
{
	if (companies[selected_company]->owned_stocks < st_io_get_input_value ())
	{
		return;
	}

	money += companies[selected_company]->value * st_io_get_input_value ();
	companies[selected_company]->owned_stocks -= st_io_get_input_value ();
}

void
st_game_process_command ()
{
	switch (st_io_get_command ())
	{
	case st_io_command_invalid:
		break;
	case st_io_command_help:
		break;
	case st_io_command_endday:
		break;
	case st_io_command_gotoday:
		going_to_day = true;
		break;
	case st_io_command_select:
		break;
	case st_io_command_buy:
		st_game_attempt_buy ();
		break;
	case st_io_command_sell:
		st_game_attempt_sell ();
		break;
	case st_io_command_exit:
		// End game and ask to shutdown
		request_exit = true;
		game_over = true;
		break;
	default:
	}
}

void
st_game_update ()
{
	if (st_io_get_command () != st_io_command_endday
		&& st_io_get_command () != st_io_command_gotoday
	)
	{
		return;
	}

	if (st_io_get_command () == st_io_command_gotoday
		&& st_io_get_input_value () <= day
	)
	{
		going_to_day = false;
		return;
	}

	++day;
	st_io_load_info_day (day);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_update (companies[i]);
	}
}

bool
st_game_run ()
{
	st_game_init ();

	while (!game_over)
	{
		st_game_update();
		st_io_load_info_company (
			companies[selected_company]->name,
			companies[selected_company]->value,
			companies[selected_company]->owned_stocks
		);
		st_io_load_info_money (money);
		st_io_draw ();

		if (going_to_day)
		{
			continue;
		}

		st_io_process_input ();
		st_game_process_command();
	}

	st_game_over_screen ();
	st_game_terminate ();

	return request_exit;
}
