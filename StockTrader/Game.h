/*------------------------------------------------------
	File Name: Game.h
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)

	Where all the main game logic is stored and executed
------------------------------------------------------*/

#pragma once
#include "Companies.h"

class Game
{
	// Functions
public:
	Game() : m_companies(nullptr), m_dataRef(nullptr), m_bitData(2) {}
	~Game()
	{
		delete[] m_companies;
		delete[] m_dataRef;
	}

	bool Startup();			//General initialisation
	void Update();			//Called to update though game functions
	void Draw();			//Prints out to console
	void UserInput();		//Asks user for input then handles it

	bool GetGameOver() const;	//Returns gameover state

private:
	bool InitialiseCompanies();			//Creation and initialisation of companies
	void StepDay();						//Moves forward one day, seperate to allow day skips
	void GotoDay(short);				//Function used to skip ahead in days
	byte GetCommand();					//Function to handle user input
	void CommenceEndGame();				//Once a year has passed game ends
	void FormInt(short[3]);				//Turns an char array into a single interger
	char GetDataFromArray(byte, byte);	//Returns the character corresponding to the data array
	void UpdateMaxValue();				//Loops through all companies checking if max value has been exceeded
	void UpdateMoneyText();				//Updates the player money text

	void DrawHeader();		//Prints out title and description
	void DrawGraph();		//Prints the graph of the current company
	void DrawInfo();		//Prints info about companies and player

	void ClearBitData();		//Clears the bitdata
	void SetZeroMessage(bool);	//Sets day zero message state
	void SetGameOver(bool);		//Sets gameover state
	void SetEndDay(bool);		//Sets endday state
	void SetHelp(bool);			//Sets help state
	void SetInvalid(bool);		//Sets invalid state
		
	bool GetZeroMessage() const;	//Returns day zero message state
	bool GetEndDay() const;			//Returns endday state
	bool GetHelp() const;			//Returns help state
	bool GetInvalid() const;		//Returns invalid state

	// Variables
private:
	byte m_bitData = 0;				//One byte encoding 8 bools: Invalid-Help-EndDay-DayZero-GameOver
	byte m_currentlySelected = 0;	//The company currently selected for display
	short m_currentDay = 0;			//Current day
	short m_targetDay = 0;			//Used when fast forwarding
	unsigned int m_maxValue = 512;	//Scales the graph, doubles when exceeded
	int m_money = 10000;			//The players cash
	string m_moneyText = "$10,000";	//The string format of money used for printing

	Companies *m_companies;		//For creating companies on the heap
	unsigned int *m_dataRef;	//A local reference for the currently selected company data
};
