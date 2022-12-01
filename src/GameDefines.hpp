#pragma once
/* Todo:
 * -Endgame
 * -Display money with commas
 * -Have the graph show a single line on the first day or pre-run the graph for width-2 days
 * https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
 */

typedef signed char			int8;
typedef signed short			int16;
typedef signed int			int32;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int			uint32;
typedef unsigned long long	uint64;

constexpr int8		int8_min		= -127-1;
constexpr int16	int16_min	= -32767-1;
constexpr int32	int32_min	= -2147483647-1;
constexpr int64	int64_min	= -9223372036854775807-1;
constexpr int8		INT8_MAX		= 127;
constexpr int16	INT16_MAX	= 32767;
constexpr int32	INT32_MAX	= 2147483647;
constexpr int64	INT64_MAX	= 9223372036854775807;
constexpr uint8	UINT8_MAX	= 0xff;
constexpr uint16	UINT16_MAX	= 0xffff;
constexpr uint32	UINT32_MAX	= 0xffffffff;
constexpr uint64	UINT64_MAX	= 0xffffffffffffffff;

constexpr uint8 CHARWIDTH = (uint8)8;			// The width of one character in the console
constexpr uint8 WIDTH = (uint8)90;				// The character width of the console window (How many characters wide)
constexpr uint8 DETAIL = (uint8)30;				// How many lines high the graph is
constexpr uint8 NUMCOMPANIES = (uint8)5;		// How many companies there are
constexpr int32 MAXTRANSFER = INT32_MAX;	// The maximum amount of stocks you can buy/sell at once
constexpr int32 STARTINGCASH = 10000;			// The amount of cash the players starts with

// Character storage
// Double lines
const char* const VERTICAL = "\xBA";
const char* const TOP_RIGHT = "\xBB";
const char* const BOTTOM_RIGHT = "\xBC";
const char* const BOTTOM_LEFT = "\xC8";
const char* const TOP_LEFT = "\xC9";
const char* const HORIZONTAL = "\xCD";
// Characters
const char* const FORWARD_SLASH = "\x2F";
const char* const BACK_SLASH = "\x5C";
const char* const FLAT_LINE = "\xC4";

// Singular state machine controls the flow of the game
enum class State: uint8
{
	Clear,
	GameOver,
	Invalid,
	Info,
	Help,
	EndDay,
	Goto,
	Select,
	Buy,
	Sell
};

// The different types of companies avaliable
enum class CompanyType: uint8
{
	UNDEFINED,
	Flat,
	Growth,
	UpNDown,
	FalseHope,
	TwinPeaks
};
