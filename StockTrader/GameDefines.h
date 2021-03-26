#pragma once
// Exactly 1 byte of information (from 0-255)
typedef unsigned char byte;
// A signed variant of byte (from -128-127)
typedef signed char sbyte;

const byte CHARWIDTH = (byte)8;		// The width of one character in the console
const byte WIDTH = (byte)90;		// The character width of the console window (How many characters wide)
const byte DETAIL = (byte)23;		// How many lines high the graph is
const byte NUMCOMPANIES = (byte)5;	// How many companies there are
const int MAXTRANSFER = 99999;		// The maximum amount of stocks you can buy/sell at once

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

// The different types of companies avaliable
const enum class CompanyType
{
	UNDEFINED,
	FLAT,
	GROWTH,
	UPNDOWN,
	FALSEHOPE,
	TWINPEAKS
};

/* Notes:
* -For bitdata theres usually only one bit flipped at a time, could potentially unify into a single value
* Todo:
* -Endgame
* -Display money with commas
* -Make buying and selling cost money
*/