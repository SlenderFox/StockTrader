/*--------------------------------------------------------
	File Name: Player.h
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)

	The player class executes commands and holds the players
		money
--------------------------------------------------------*/

#pragma once

class Player
{
	// Functions
public:
	Player();
	~Player();

	int ExecuteCommand(int command);	//Function to handle commands
	void UpdateMoneyName();					//Updates the players money each day

	// Variables
public:
	char m_moneyName[15] = "$10,000";		//Used for displaying the players money
	int m_currentlySelected;						//The currently selected company
	int m_money = 10000;							//The players money
};
