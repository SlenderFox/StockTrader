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

void
st_io_buff_set (uint32_t _row, uint32_t _column, char _val);

void
st_io_buff_set_row (uint32_t _row, const char *_val);
