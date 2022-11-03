#pragma once

// Exactly 1 byte of information (from 0-255)
typedef unsigned char byte;
// A signed variant of byte (from -128-127)
typedef signed char sbyte;

const byte CHARWIDTH = (byte)8;		// The width of one character in the console
const byte WIDTH = (byte)90;		// The character width of the console window (How many characters wide)
const byte DETAIL = (byte)30;		// How many lines high the graph is
const byte NUMCOMPANIES = (byte)5;	// How many companies there are
const int MAXTRANSFER = 0xFFFFF;	// The maximum amount of stocks you can buy/sell at once
const int STARTINGCASH = 10000;		// The amount of cash the players starts with

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
enum class State : byte
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
const enum class CompanyType
{
	UNDEFINED,
	Flat,
	Growth,
	UpNDown,
	FalseHope,
	TwinPeaks
};

/* Todo:
* -Endgame
* -Display money with commas
* -Have the graph show a single line on the first day or pre-run the graph for width-2 days
* https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
*/