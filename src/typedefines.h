#pragma once

typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;
typedef signed long long   int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

int8    INT8_MIN    = -127-1;
int16   INT16_MIN   = -32767-1;
int32   INT32_MIN   = -2147483647-1;
int64   INT64_MIN   = -9223372036854775807-1;
int8    INT8_MAX    = 127;
int16   INT16_MAX   = 32767;
int32   INT32_MAX   = 2147483647;
int64   INT64_MAX   = 9223372036854775807;
uint8   UINT8_MAX   = 0xff;
uint16  UINT16_MAX  = 0xffff;
uint32  UINT32_MAX  = 0xffffffff;
uint64  UINT64_MAX  = 0xffffffffffffffff;
