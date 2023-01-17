#pragma once
#include <stdint.h>

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
