#pragma once
#include "Company.h"
#include <iostream>

enum class State : byte { Clear, GameOver, Invalid, EndDay, Info, Help };

class Game
{
public:
	Game() : m_companies(nullptr), m_dataRef(nullptr) {}
	~Game()
	{
		delete[] m_companies;
		delete[] m_dataRef;
	}

	// Intiates the app
	void Run();

private:
	// Called once when the application starts
	bool Startup();
	// The main loop of the program happens in here
	bool Update();
	// Prints the graph of the current company
	void DrawGraph();
	// Prints info about companies and player
	void DrawInfo();
	// Prints the in-game console
	void DrawConsole();
	// Asks user for input then handles it
	void UserInput();

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

	// Resets the current state
	void ResetState() { m_state = State::Clear; }

	// Sets gameover state
	void SetGameOver() { m_state = State::GameOver; }
	// Sets state to invalid
	void SetInvalid(string pMessage);
	// Sets state to EndDay
	void SetEndDay() { m_state = State::EndDay; }
	// Sets state to Info
	void SetInfo() { m_state = State::Info; }
	// Sets state to Help
	void SetHelp() { m_state = State::Help; }

	// Returns gameover state
	bool GetGameOver() const { return (m_state == State::GameOver) ? true : false; }
	// Returns invalid state
	bool GetInvalid() const { return (m_state == State::Invalid) ? true : false; }
	// Returns endday state
	bool GetEndDay() const { return (m_state == State::EndDay) ? true : false; }
	// Returns day zero message state
	bool GetInfo() const { return (m_state == State::Info) ? true : false; }
	// Returns help state
	bool GetHelp() const { return (m_state == State::Help) ? true : false; }

	State m_state = State::Info;	// Controls what the game should do
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
