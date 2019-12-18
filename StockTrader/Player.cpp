/*--------------------------------------------------------
	File Name: Player.cpp
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)
--------------------------------------------------------*/

#include "Player.h"
#include "GameDefines.h"
#include "Game.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

Player::Player() {}

Player::~Player() {}

int Player::ExecuteCommand(int command)
{
	// Requests to select one of the companies
	if (command <= TWINPEAKS)
	{
		m_currentlySelected = command;
		return 0;
	}
	else
	{
		// Requests for the current day to be ended
		if (command == ENDDAY)
		{
			return 1;
		}

		// Displays commands
		if (command == HELP)
		{
			cout << "\nCommands are:\n"
				<< "'help'                  | Lists these commands\n"
				<< "'select' <company name> | Chooses the current company to be displayed\n"
				<< "'end day' or 'n'        | Ends current day and moves on to the next\n"
				<< "'goto <day>'            | Skips ahead to selected day\n\n"
				<< "NOTE: All commands are lower case.\n\n"
				<< "Press 'Enter' to continue...";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			return 0;
		}

		// Requests to fast forward
		if (command == FASTFORWARD)
		{
			return 2;
		}
	}
}

void Player::UpdateMoneyName()
{
	// Adds comma's to number for printing so it is easier to read

}
