#include "io.h"
#include "company.h"
#include "game.h"

#ifndef MIN
	#define MIN(_a, _b) ((_a < _b) ? _a : _b)
#endif

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
uint16_t selected_company = 0;
uint32_t day = 0, target_day = 0;
int64_t money = 1000;

char *company_names[COMPANIES] = {
	"Company Number 1",
	"Company Number 2",
	"Company Number 3",
	"Company Number 4",
	"Company Number 5"
};

void
st_game_init ()
{
	st_io_init (ROWS, COLUMNS);

	for (uint16_t i = 0; i < COMPANIES; ++i)
	{
		st_company_construct (&(companies[i]), company_names[i]);
	}
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
st_game_attempt_goto ()
{
	uint32_t val = st_io_get_input_value ();
	if (val > YEAR || day >= val)
	{
		st_io_set_invalid_message ("Invalid goto day");
		return;
	}
	target_day = val;
}

void
st_game_attempt_select ()
{
	uint16_t val = st_io_get_input_value ();
	if (val < 0U || val > COMPANIES)
	{
		return;
	}
	selected_company = val - 1;
}

void
st_game_attempt_buy ()
{
	uint32_t val = st_io_get_input_value ();
	if (money < companies[selected_company]->value * val)
	{
		return;
	}
	money -= companies[selected_company]->value * val;
	companies[selected_company]->owned_stocks += val;
}

void
st_game_attempt_sell ()
{
	uint32_t val = st_io_get_input_value ();
	if (companies[selected_company]->owned_stocks < val)
	{
		return;
	}
	money += companies[selected_company]->value * val;
	companies[selected_company]->owned_stocks -= val;
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
		st_game_attempt_goto ();
		break;
	case st_io_command_select:
		st_game_attempt_select ();
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
	// Game end
	if (day == YEAR)
	{
		target_day = 0;
		game_over = true;
		request_exit = true; // TEMP
		return;
	}

	// Do not increment the day
	if (st_io_get_command () != st_io_command_endday
		&& st_io_get_command () != st_io_command_gotoday
	)
	{
		return;
	}

	// Cancel goto
	if (st_io_get_command () == st_io_command_gotoday
		&& target_day <= day
	)
	{
		target_day = 0;
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
		st_game_update ();
		st_io_load_info_company (
			companies[selected_company]->name,
			companies[selected_company]->value,
			companies[selected_company]->owned_stocks
		);
		st_io_load_info_money (money);
		st_io_draw ();

		if (target_day > day)
		{
			continue;
		}

		st_io_process_input ();
		st_game_process_command ();
	}

	st_game_over_screen ();
	st_game_terminate ();

	return request_exit;
}
