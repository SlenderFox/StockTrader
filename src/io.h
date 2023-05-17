#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The state of the game that defines the behaviour for the next print */
typedef enum st_io_command_t
{
	st_io_command_invalid,
	st_io_command_help,
	st_io_command_endday,
	st_io_command_gotoday,
	st_io_command_select,
	st_io_command_buy,
	st_io_command_sell,
	st_io_command_exit
}
st_io_command_t;

/** Constructs all the buffers
 * @param _rows How many rows the graph will have
 * @param _columns How many columns the graph will have
 */
void
st_io_init (uint16_t _rows, uint16_t _columns);

/** Deconstructs all the buffers */
void
st_io_terminate ();

/** Outputs the contents of the buffer to the standard output */
void
st_io_draw ();

/** Clears the terminal on the current OS */
void
st_io_clear ();

/** Take input from the user and convert it into a command */
void
st_io_process_input ();

/** After processing the input, call this function to get the command
 * @return [st_io_command_t] The command that was processed most recently
 */
st_io_command_t
st_io_get_command ();

/** Most inputs also require a value to be passed
 * @return [double] The value received from the user
 */
double
st_io_get_input_value ();

/** Sets the message to be printed when the command is invalid
 * @param _message The message
 * @todo Cap message length
 * @todo Load invalid message into buffer correctly
 */
void
st_io_set_invalid_message (char *_message);

/** Print the current invalid message
 * @todo REMOVE
*/
void
st_io_print_invalid_message ();

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

#ifdef __cplusplus
} // extern "C"
#endif
