#pragma once
#include "Company.h"

class Game
{
	// Functions
public:
	Game() : m_companies(nullptr), m_dataRef(nullptr) {}
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
	// Returns the character corresponding to the data array
	char GetDataFromArray(byte pHorizontal, byte pVertical);
	// Loops through all companies checking if max value has been exceeded
	void UpdateMaxValue();
	// Updates the player money text
	void UpdateMoneyText();
	// Attempts to buy or sell stocks from the currently selected company
	void BuySellFromCompany(int pAmount);

	// Prints the graph of the current company
	void DrawGraph();
	// Prints info about companies and player
	void DrawInfo();
	// Prints the in-game console
	void DrawConsole();

	// Returns day zero message state
	bool GetZeroMessage() const;
	// Returns endday state
	bool GetEndDay() const;
	// Returns help state
	bool GetHelp() const;
	// Returns invalid state
	bool GetInvalid() const;

	// Resets the current state
	void ResetState() { m_state = State::Clear; }
	// Sets gameover state
	void SetGameOver() { m_state = State::GameOver; }
	// Sets day zero message state
	void SetZeroMessage() { m_state = State::DayZero; }
	// Sets endday state
	void SetEndDay() { m_state = State::EndDay; }
	// Sets help state
	void SetHelp() { m_state = State::Help; }
	// Sets invalid state
	void SetInvalid(string pMessage);

	// Variables
private:
	enum class State : byte { Clear, GameOver, DayZero, EndDay, Help, Invalid };
	State m_state = State::DayZero;	// Controls what the game should do
	byte m_selected = 0;			// The company currently selected for display
	short m_day = 0;				// The current day
	short m_targetDay = 0;			// Used when fast forwarding
	unsigned int m_maxValue = 512;	// Scales the graph, doubles when exceeded
	int m_money = 10000;			// The players cash
	string m_moneyText = "$10,000";	// The string format of money used for printing
	string m_invalidMessage = "";	// A message to be printed in case of invalid input

	Company *m_companies;		// For creating companies on the heap
	unsigned int *m_dataRef;	// A local reference for the currently selected company data
};
