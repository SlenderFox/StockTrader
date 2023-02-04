#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The state of the game that defines the behaviour for the next print */
enum st_io_command_e
{
	st_io_command_invalid,
	st_io_command_help,
	st_io_command_endday,
	st_io_command_gotoday,
	st_io_command_select,
	st_io_command_buy,
	st_io_command_sell
};

typedef enum st_io_command_e st_io_command_t;

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
st_io_process_input ();

st_io_command_t
st_io_get_command ();

double
st_io_get_input_value ();

void
st_io_print_invalid_message ();

#ifdef __cplusplus
}
#endif
