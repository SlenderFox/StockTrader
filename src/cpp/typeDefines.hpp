#pragma once

#define _NODISCARD [[nodiscard]]

namespace stockTrader
{
	typedef signed char        int8;
	typedef signed short       int16;
	typedef signed int         int32;
	typedef signed long long   int64;
	typedef unsigned char      uint8;
	typedef unsigned short     uint16;
	typedef unsigned int       uint32;
	typedef unsigned long long uint64;

	constexpr int8    INT8_MIN    = -127-1;
	constexpr int16   INT16_MIN   = -32767-1;
	constexpr int32   INT32_MIN   = -2147483647-1;
	constexpr int64   INT64_MIN   = -9223372036854775807-1;
	constexpr int8    INT8_MAX    = 127;
	constexpr int16   INT16_MAX   = 32767;
	constexpr int32   INT32_MAX   = 2147483647;
	constexpr int64   INT64_MAX   = 9223372036854775807;
	constexpr uint8   UINT8_MAX   = 0xff;
	constexpr uint16  UINT16_MAX  = 0xffff;
	constexpr uint32  UINT32_MAX  = 0xffffffff;
	constexpr uint64  UINT64_MAX  = 0xffffffffffffffff;

	constexpr uint8 CHARWIDTH = 8;           // The width of one character in the console
	constexpr uint8 WIDTH = 90;              // The character width of the console window (How many characters wide)
	constexpr uint8 DETAIL = 30;             // How many lines high the graph is
	constexpr uint8 NUMCOMPANIES = 5;        // How many companies there are
	constexpr int32 MAXTRANSFER = INT32_MAX; // The maximum amount of stocks you can buy/sell at once
	constexpr int32 STARTINGCASH = 10000;    // The amount of cash the players starts with

	// Character storage
	// Double lines
	constexpr const char *const VERTICAL      = "|";
	constexpr const char *const TOP_RIGHT     = "+";
	constexpr const char *const BOTTOM_RIGHT  = "+";
	constexpr const char *const BOTTOM_LEFT   = "+";
	constexpr const char *const TOP_LEFT      = "+";
	constexpr const char *const HORIZONTAL    = "-";
	// Characters
	constexpr const char *const FORWARD_SLASH = "\x2F";
	constexpr const char *const BACK_SLASH    = "\x5C";
	constexpr const char *const FLAT_LINE     = "-";
}
