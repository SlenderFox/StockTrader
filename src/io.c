#include <stdio.h> // printf, snprintf
#include <stdbool.h> // bool, true, false
#include <string.h> // strlen
#include <assert.h> // assert
#include <stdlib.h> // system, malloc, realloc, free

#include "io.h"
#include "buffer.h"
#include "utils.h"

enum { MIN_GRAPH_ROWS = 4 };
enum { MIN_GRAPH_COLS = 20 };

// Title and vetical graph border
enum { GRAPH_PADDING_ROW = 3 };
// Side graph border
enum { GRAPH_PADDING_COL = 2 };
enum { INFO_LENGTH = 6 };

bool loaded = false;
const char clear_char = ' ';

uint16_t total_rows = 0, total_columns = 0;
uint16_t graph_rows = 0, graph_columns = 0;
uint16_t row_overflow = 0;

uint16_t info_offset = 0;

st_buffer_t *buffer_a, *buffer_b, **buffer_active, **buffer_inactive;

st_io_request_t command = st_io_request_invalid;
double input_value = 0;
char *invalid_message;

// ----- Local functions ------

/** Will place a formatted value into the info panel
 * @param _offset The offset within the info panel
 * @param _format The string formatting applied to the value (use %s for value)
 * @param _value The value in question, must be int, uint, double, or string
 * @param _type The type of the string as single char, follows fmt (d,u,f,s)
 * @remark Passing a shorter type (float, int, short) is undefined behaviour
 */
void
st_io_load_info (
	uint8_t _offset,
	char *_format,
	void *_value,
	char _type
)
{
	int valueLength;
	char *value = NULL;

	switch (_type)
	{
	case 'd': // int
		int32_t dval = *(int32_t*)_value;
		valueLength = snprintf (NULL, 0, "%d", dval);
		value = malloc (++valueLength);
		snprintf (value, valueLength, "%d", dval);
		break;
	case 'u': // unsigned int
		uint32_t uval = *(uint32_t*)_value;
		valueLength = snprintf (NULL, 0, "%u", uval);
		value = malloc (++valueLength);
		snprintf (value, valueLength, "%u", uval);
		break;
	case 'f': // float (double)
		double fval = *(double*)_value;
		valueLength = snprintf (NULL, 0, "%.2f", fval);
		value = malloc (++valueLength);
		snprintf (value, valueLength, "%.2f", fval);
		break;
	case 's': // string
		char *cval = (char*)_value;
		valueLength = strlen (cval);
		value = malloc (valueLength);
		snprintf (value, valueLength, "%s", cval);
		break;
	default: // handle error
		return;
	}

	// Make last character a null terminator
	value[valueLength - 1] = '\0';

	int totalLength = strlen (_format) + valueLength;
	char *input = malloc (totalLength);
	snprintf (input, totalLength, _format, value);

	st_buff_data_row_insert (*buffer_active, info_offset + _offset, 0, input);

	free (value);
	free (input);
}

/** Parse stdin looking for a valid command
 * @return [int] -1 for failure
*/
int
st_io_process_command ()
{
	/* Maybe make an array of strings (char*)
	 * only allow alphanumeric characters and space
	 * 0-9 = 48-57
	 * A-Z = 65-90
	 * a-z = 97-122
	 * space = 32
	*/

	// Read up to 6 lower case letters or until a whitespace
	//scanf ("%6[a-z]");

	return 0;
}

/** Parse stdin looking for a valid value to go with the current command
 * @return [int] -1 for failure
 */
int
st_io_process_value ()
{
	return 0;
}

void
st_io_set_invalid_message (char *_message)
{
	(*invalid_message) = *_message;
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
	assert (loaded && "io not yet loaded\n");

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
	assert (loaded && "io not yet loaded\n");

	st_io_load_title ("STOCKTRADER");
	st_io_load_graph_frame ();
	st_io_load_info_day (69);
	st_io_load_info_money (10000);
	st_io_load_info_company ("Company", 0.01, 50);
	st_buff_data_row_set (*buffer_active, info_offset + 5, '-');
}

void
st_io_draw ()
{
	assert (loaded && "io not yet loaded\n");

	// Move cursor back to start
	printf ("\e[%uF", total_rows + row_overflow);

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
	assert (loaded && "io not yet loaded\n");

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
	// TODO
}

void
st_io_load_info_day  (uint32_t _day)
{
	assert (loaded && "io not yet loaded\n");
	st_io_load_info (0, "Day: %s", &_day, 'u');
}

void
st_io_load_info_money (double _money)
{
	assert (loaded && "io not yet loaded\n");
	st_io_load_info (1, "Money: $%s", &_money, 'f');
}

void
st_io_load_info_company (
	char *_name,
	double _value,
	uint32_t _owned
)
{
	assert (loaded && "io not yet loaded\n");
	st_io_load_info (2, "%s:", _name, 's');
	st_io_load_info (3, "   $%s per", &_value, 'f');
	st_io_load_info (4, "   %s owned", &_owned, 'u');
}

void
st_io_process_input ()
{
	assert (loaded && "io not yet loaded\n");
	printf ("> ");
	st_io_process_command ();
	st_io_process_value ();
}

st_io_request_t
st_io_get_request ()
{
	return command;
}

double
st_io_get_input_value ()
{
	return input_value;
}

char *
st_io_get_invalid_message ()
{
	return invalid_message;
}
