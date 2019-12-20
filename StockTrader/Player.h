/*--------------------------------------------------------
	File Name: Player.h
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)

	The player class stores player money and stocks
--------------------------------------------------------*/

#pragma once
#include "GameDefines.h"

class Player
{
	// Functions
public:
	Player() {}
	~Player() {}

	int GetMoney() const { return m_money; }		//Returns how much money the player has

	// Variables
private:
	char m_moneyName[15] = "$10,000";	//Used for displaying the players money
	int m_money = 10000;						//The players money
};
