#pragma once
#include "buffer.h"

uint64 st_io_buffer_vertical = 5;
uint64 st_io_buffer_horizontal = 5;

st_buffer *st_io_buffer_a;
st_buffer *st_io_buffer_b;

st_buffer **st_io_buffer_active;
st_buffer **st_io_buffer_inactive;
