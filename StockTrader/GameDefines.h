/*----------------------------------------------
	File Name: GameDefines.h
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)

	Holds constant, global variables
----------------------------------------------*/

#pragma once
// Exactly 1 byte of information (from 0-255)
typedef unsigned char byte;
// A signed variant of byte (from -128-127)
typedef signed char sbyte;

const byte WIDTH = 90;		//The character width of the console window (How many characters wide)
const byte DETAIL = 20;		//How many lines high the graph is
const byte COMPAMOUNT = 5;	//How many companies there are

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

// Input controls
const enum Input : byte
{
	HELP,
	ENDDAY,
	FASTFORWARD,
	BUY,
	SELL,
	SELECT_ONE,
	SELECT_TWO,
	SELECT_THREE,
	SELECT_FOUR,
	SELECT_FIVE,
	INVALID
};

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