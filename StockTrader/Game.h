/*------------------------------------------------------
	Filename: Game.h
	Author: Dylan Glenister
	Modified: 25/02/21 (dd/mm/yy)

	Where all the main game logic is stored and executed
------------------------------------------------------*/

#pragma once
#include "Company.h"

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

	// Called once when the application starts
	bool Startup();
	// Called each time a user enters an input
	void Update();
	// Draws the text to the console window
	void Draw();
	// Asks user for input then handles it
	void UserInput();

	// Returns gameover state
	bool GetGameOver() const;

private:
	// Creation and initialisation of companies
	bool InitialiseCompanies();
	// Moves forward one day
	void StepDay();
	// Repeatedly calls StepDay() until the target day is reached
	void GotoDay(short pTargetDay);
	// Once a year has passed game ends
	void CommenceEndGame();
	// Turns a char array into a single interger
	void FormInt(short pTargetDay[3]);
	// Returns the character corresponding to the data array
	char GetDataFromArray(byte pHorizontal, byte pVertical);
	// Loops through all companies checking if max value has been exceeded
	void UpdateMaxValue();
	// Updates the player money text
	void UpdateMoneyText();

	// Prints out title and description
	void DrawHeader();
	// Prints the graph of the current company
	void DrawGraph();
	// Prints info about companies and player
	void DrawInfo();

	// Clears the bitdata
	void ClearBitData();
	// Sets day zero message state
	void SetZeroMessage(bool pState);
	// Sets gameover state
	void SetGameOver(bool pState);
	// Sets endday state
	void SetEndDay(bool pState);
	// Sets help state
	void SetHelp(bool pState);
	// Sets invalid state
	void SetInvalid(bool pState);

	// Returns day zero message state
	bool GetZeroMessage() const;
	// Returns endday state
	bool GetEndDay() const;
	// Returns help state
	bool GetHelp() const;
	// Returns invalid state
	bool GetInvalid() const;

	// Variables
private:
	byte m_bitData = 0;				// One byte encoding up to 8 bools: Invalid-Help-EndDay-DayZero-GameOver
	byte m_currentlySelected = 0;	// The company currently selected for display
	short m_currentDay = 0;			// Current day
	short m_targetDay = 0;			// Used when fast forwarding
	unsigned int m_maxValue = 512;	// Scales the graph, doubles when exceeded
	int m_money = 10000;			// The players cash
	string m_moneyText = "$10,000";	// The string format of money used for printing

	Company *m_companies;		// For creating companies on the heap
	unsigned int *m_dataRef;	// A local reference for the currently selected company data
};
