#pragma once

typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;
typedef signed long long   int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

#define INT8_MIN   -127-1;
#define INT16_MIN  -32767-1;
#define INT32_MIN  -2147483647-1;
#define INT64_MIN  -9223372036854775807-1;
#define INT8_MAX   127;
#define INT16_MAX  32767;
#define INT32_MAX  2147483647;
#define INT64_MAX  9223372036854775807;
#define UINT8_MAX  0xff;
#define UINT16_MAX 0xffff;
#define UINT32_MAX 0xffffffff;
#define UINT64_MAX 0xffffffffffffffff;
