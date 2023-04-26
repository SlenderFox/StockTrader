#include <stdio.h> // printf, snprintf
#include <stdbool.h> // bool, true, false
#include <string.h> // strlen
#include <strings.h> // strcasecmp
#include <assert.h> // assert
#include <stdlib.h> // system, malloc, realloc, free

#include "io.h"
#include "buffer.h"
#include "utils.h"

// Constants
enum {
	MIN_GRAPH_ROWS = 4,
	MIN_GRAPH_COLS = 20,

	// Title and vetical graph border
	GRAPH_PADDING_ROW = 3,
	// Side graph border
	GRAPH_PADDING_COL = 2,
	INFO_LENGTH = 6
};

bool loaded = false;
#define CHECK_LOADED assert (loaded && "io not yet loaded\n");

bool ready_for_value = false;

const char clear_char = ' ';

/** The amount of rows and columns in the render buffer */
uint16_t total_rows = 0, total_columns = 0;
/** The amount of rows and coloums available to the graph */
uint16_t graph_rows = 0, graph_columns = 0;
//uint16_t row_overflow = 0;

uint16_t info_offset = 0;

st_buffer_t *buffer_a, *buffer_b, **buffer_active, **buffer_inactive;

st_io_command_t command = st_io_command_none;
double input_value = 0;
char *invalid_message;

// ----- Local functions ------

/** Will place a formatted value into the info panel
 * @param _offset The row offset within the info panel
 * @param _format The string formatting applied to the value (use %s for value)
 * @param *_value The string to be loaded into the info panel
 * @param _valueLength How long the string is
 * @todo Does not check if overflowing the buffer width
 */
void
st_io_load_info (
	uint8_t _offset,
	char *_format,
	char *_value,
	uint8_t _valueLength
)
{
	int totalLength = strlen (_format) + _valueLength;
	char *input = malloc (totalLength);
	snprintf (input, totalLength, _format, _value);
	st_buff_data_row_insert (*buffer_active, info_offset + _offset, 0, input);
	free (input);
}

void
st_io_load_info_int(
	uint8_t _offset,
	char *_format,
	int32_t _value
)
{
	int strLength = snprintf (NULL, 0, "%d", _value) + 1;
	char *valString = malloc (strLength);
	snprintf (valString, strLength, "%d", _value);
	st_io_load_info (_offset, _format, valString, strLength);
	free (valString);
}

void
st_io_load_info_uint(
	uint8_t _offset,
	char *_format,
	uint32_t _value
)
{
	int strLength = snprintf (NULL, 0, "%u", _value) + 1;
	char *valString = malloc (strLength);
	snprintf (valString, strLength, "%u", _value);
	st_io_load_info (_offset, _format, valString, strLength);
	free (valString);
}

void
st_io_load_info_double(
	uint8_t _offset,
	char *_format,
	double _value
)
{

	int strLength = snprintf (NULL, 0, "%.2f", _value) + 1;
	char *valString = malloc (strLength);
	snprintf (valString, strLength, "%.2f", _value);
	st_io_load_info (_offset, _format, valString, strLength);
	free (valString);
}

void
st_io_load_info_string(
	uint8_t _offset,
	char *_format,
	char *_value
)
{
	int strLength = strlen (_value) + 1;
	st_io_load_info (_offset, _format, _value, strLength);
}

void
st_io_set_invalid_message (char *_message)
{
	strncpy (invalid_message, _message, 99);
}

/** Parse stdin looking for a valid command */
void
st_io_process_command ()
{
	char input[16] = "\0";
	int res = scanf ("%15s", input);
	if (res == 0)
	{
		command = st_io_command_invalid;
		st_io_set_invalid_message ("Invalid input");
		return;
	}

	if (strcasecmp (input, "help") == 0
		|| strcasecmp (input, "h") == 0
	)
	{
		command = st_io_command_help;
		return;
	}

	if (strcasecmp (input, "endday") == 0
		|| strcasecmp (input, "end") == 0
		|| strcasecmp (input, "e") == 0
		|| strcasecmp (input, "next") == 0
		|| strcasecmp (input, "n") == 0
	)
	{
		command = st_io_command_endday;
		return;
	}

	if (strcasecmp (input, "gotoday") == 0
		|| strcasecmp (input, "goto") == 0
		|| strcasecmp (input, "g") == 0
	)
	{
		command = st_io_command_gotoday;
		ready_for_value = true;
		return;
	}

	if (strcasecmp (input, "select") == 0
		|| strcasecmp (input, "c") == 0
	)
	{
		command = st_io_command_select;
		ready_for_value = true;
		return;
	}

	if (strcasecmp (input, "buy") == 0
		|| strcasecmp (input, "b") == 0
	)
	{
		command = st_io_command_buy;
		ready_for_value = true;
		return;
	}

	if (strcasecmp (input, "sell") == 0
		|| strcasecmp (input, "s") == 0
	)
	{
		command = st_io_command_sell;
		ready_for_value = true;
		return;
	}

	if (strcasecmp (input, "exit") == 0)
	{
		command = st_io_command_exit;
		return;
	}

	command = st_io_command_invalid;
	st_io_set_invalid_message ("Command not found");
}

/** Parse stdin looking for a valid value to go with the current command */
void
st_io_process_value ()
{
	if (!ready_for_value)
	{
		return;
	}

	char input[64] = "\0";
	int res = scanf ("%63s", input);
	if (res == 0)
	{
		command = st_io_command_invalid;
		st_io_set_invalid_message ("Invalid input");
		return;
	}

	if (input[0] == '\0')
	{
		command = st_io_command_invalid;
		st_io_set_invalid_message ("No input provided");
		return;
	}

	uint8_t endpos = 0;

	// Verify only numbers or decimal place present
	for (uint8_t i = 0; i < 64; ++i)
	{
		if (input[i] == '\0')
		{
			endpos = i;
			break;
		}

		// Intended to "fail quickly"
		if (input[i] != '0'
			&& input[i] != '1'
			&& input[i] != '2'
			&& input[i] != '3'
			&& input[i] != '4'
			&& input[i] != '5'
			&& input[i] != '6'
			&& input[i] != '7'
			&& input[i] != '8'
			&& input[i] != '9'
			&& input[i] != '.'
		)
		{
			command = st_io_command_invalid;
			st_io_set_invalid_message ("Incorrect input");
			return;
		}
	}

	char *end = &(input[endpos]);
	input_value = strtod (input, &end);

	ready_for_value = false;
}

void
st_io_print_invalid_message ()
{
	printf ("%s\n", invalid_message);
}

void
st_io_print_command ()
{
	switch (st_io_get_command ())
	{
	default:
	//	assert ("Unexpected control path");
	case st_io_command_none:
		// Just print nothing
		break;
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
		printf ("Gotoday %f\n", st_io_get_input_value ());
		break;
	case st_io_command_select:
		printf ("Select %f\n", st_io_get_input_value ());
		break;
	case st_io_command_buy:
		printf ("Buy %f\n", st_io_get_input_value ());
		break;
	case st_io_command_sell:
		printf ("Sell %f\n", st_io_get_input_value ());
		break;
	case st_io_command_exit:
		printf ("Exit now\n");
		break;
	}
}

// ----- Public Functions -----

void
st_io_init (uint16_t _rows, uint16_t _columns)
{
	graph_rows = MAX (_rows, MIN_GRAPH_ROWS);
	graph_columns = MAX (_columns, MIN_GRAPH_COLS);

	info_offset = graph_rows + GRAPH_PADDING_ROW;
	total_rows = info_offset + INFO_LENGTH;
	total_columns = graph_columns + GRAPH_PADDING_COL;

	// Buffer a
	st_buff_construct (&buffer_a, total_rows, total_columns);
	st_buff_data_init (buffer_a);
	st_buff_data_clear (buffer_a, clear_char);
	buffer_active = &buffer_a;

	// Buffer b
	st_buff_construct (&buffer_b, total_rows, total_columns);
	st_buff_data_init (buffer_b);
	st_buff_data_clear (buffer_b, clear_char);
	buffer_inactive = &buffer_b;

	st_io_clear ();

	// Give enough room to print
	for (uint16_t i = 0; i < total_rows; ++i)
	{
		printf ("\n");
	}
	fflush (stdout);

	// Initialise the invalid input message
	invalid_message = malloc (sizeof(char) * 100);

	loaded = true;
}

void
st_io_terminate ()
{
	CHECK_LOADED

	// Buffer a
	st_buff_data_terminate (buffer_a);
	st_buff_destruct (buffer_a);

	// Buffer b
	st_buff_data_terminate (buffer_b);
	st_buff_destruct (buffer_b);

	free (invalid_message);
}

void
st_io_init_graph ()
{
	CHECK_LOADED

	st_io_load_title ("STOCKTRADER");
	st_io_load_graph_frame ();
	st_io_load_info_day (0);
	st_io_load_info_money (0);
	st_io_load_info_company ("Unknown", 0.00, 0);
	st_buff_data_row_set (*buffer_active, info_offset + 5, '-');
}

void
st_io_draw ()
{
	CHECK_LOADED

	// Move cursor back to start
	//printf ("\e[%uF", total_rows + row_overflow);

	// Temporarily clear whole screen instead of above
	st_io_clear ();

	// Output the contents of the active buffer
	for (uint16_t y = 0; y < total_rows; ++y)
	{
		char out[total_columns + 1];
		out[total_columns] = '\0';
		for (uint16_t x = 0; x < total_columns; ++x)
		{
			out[x] = st_buff_data_get (*buffer_active, y, x);
		}
		printf ("%s\n", out);
	}
	st_io_print_command ();
	fflush (stdout);
}

void
st_io_clear ()
{
	#ifdef __WIN32
	 system ("cls");
	#else
	 system ("clear");
	#endif
}

void
st_io_load_title (char *_title)
{
	st_buff_data_row_insert (*buffer_active, 0, 0, _title);
}

void
st_io_load_graph_frame ()
{
	CHECK_LOADED

	// Graph top edge
	st_buff_data_row_set (*buffer_active, 1, '=');
	st_buff_data_set (*buffer_active, 1, 0, '+');
	st_buff_data_set (*buffer_active, 1, total_columns, '+');

	// Graph side edges
	for (uint16_t i = 0; i < graph_rows; ++i)
	{
		st_buff_data_set (*buffer_active, i + 2, 0, '|');
		st_buff_data_set (*buffer_active, i + 2, total_columns, '|');
	}

	// Graph bottom  edge
	st_buff_data_row_set (*buffer_active, info_offset - 1, '=');
	st_buff_data_set (*buffer_active, info_offset - 1, 0, '+');
	st_buff_data_set (*buffer_active, info_offset - 1, total_columns, '+');
}

void
st_io_load_graph_data ()
{
	/* TODO
	 * graph_rows and graph_columns provide info about the dimensions of the graph
	*/
}

void
st_io_load_info_day  (uint32_t _day)
{
	CHECK_LOADED
	st_io_load_info_uint (0, "Day: %s", _day);
}

void
st_io_load_info_money (double _money)
{
	CHECK_LOADED
	st_io_load_info_double (1, "Money: $%s", _money);
}

void
st_io_load_info_company (
	char *_name,
	double _value,
	uint32_t _owned
)
{
	CHECK_LOADED
	st_io_load_info_string (2, "%s:", _name);
	st_io_load_info_double (3, "   $%s per", _value);
	st_io_load_info_uint (4, "   %s owned", _owned);
}

void
st_io_process_input ()
{
	CHECK_LOADED

	// Clear previous values
	command = st_io_command_invalid;
	input_value = 0;
	st_io_set_invalid_message ("No command processed");

	// Clear the input
	fflush (stdin);

	// Print prompt
	printf ("> ");
	st_io_process_command ();
	st_io_process_value ();
}

st_io_command_t
st_io_get_command ()
{
	return command;
}

double
st_io_get_input_value ()
{
	return input_value;
}
