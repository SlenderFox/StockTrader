#pragma once
#include <stdint.h>

/** The state of the game that defines the behaviour for the next print */
enum game_state
{
	invalid,
	clear,
	gameover,
	info,
	help,
	endday,
	gotoday,
	select,
	buy,
	sell
};

/** Constructs all the buffers
 * @param _rows How many rows the graph will have
 * @param _columns How many columns the graph will have
 */
void
st_io_init (uint16_t _rows, uint16_t _columns);

/** Deconstructs all the buffers */
void
st_io_terminate ();

void
st_io_init_graph ();

/** Outputs the contents of the buffer to the standard output */
void
st_io_draw ();

void
st_io_clear ();

void
st_io_load_title (char *_title);

void
st_io_load_graph_frame ();

void
st_io_load_graph_data ();

void
st_io_load_info_day (uint32_t _day);

void
st_io_load_info_money (double _money);

void
st_io_load_info_company (
	char *_name,
	double _value,
	uint32_t _owned
);

void
st_io_load_info_separator ();

void
st_io_process_input ();
