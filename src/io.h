#pragma once
#include "buffer.h"

void
st_io_init ();

void
st_io_terminate ();

/** Outputs the contents of the buffer to the standard output */
void
st_io_draw ();

uint32_t
st_io_buff_vert ();

uint32_t
st_io_buff_hori ();

uint32_t
st_io_buff_square ();
