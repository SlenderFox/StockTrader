/*----------------------------------------------
	File Name: GameDefines.h
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)

	Holds constant, global variables
----------------------------------------------*/

#pragma once
typedef unsigned char byte;

const byte WIDTH = 80;	//The character width of the console window
const byte DETAIL = 30;	//How many lines high the graph is

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
const char* const INDENT = "\t";

// Input controls
const enum Input
{
	HELP = 0,
	ENDDAY,
	FASTFORWARD,
	SELECT,
	BUY,
	SELL
};

// The different types of companies avaliable
const enum CompanyType
{
	UNDEFINED = 0,
	FLAT,
	GROWTH,
	UPNDOWN,
	FALSEHOPE,
	TWINPEAKS
};
