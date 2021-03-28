#pragma once
#include "Company.h"
#include <iostream>

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
	// Returns the character corresponding to the data array
	char GetDataFromArray(byte pHorizontal, byte pVertical);
	// Loops through all companies checking if max value has been exceeded
	void UpdateMaxValue();
	// Updates the player money text
	void UpdateMoneyText();
	// Attempts to buy or sell stocks from the currently selected company
	void BuySellFromCompany(int pAmount);

	// Sets state to invalid and modifies the invalid message
	void SetInvalid(string pMessage);

	// Resets the current state
	void ResetState() { m_state = State::Clear; }

	// Sets m_stateto GameOver
	void SetGameOver() { m_state = State::GameOver; }
	// Sets m_state to Info
	void SetInfo() { m_state = State::Info; }
	// Sets m_state to Help
	void SetHelp() { m_state = State::Help; }
	// Sets m_state to EndDay
	void SetEndDay() { m_state = State::EndDay; }
	// Sets m_state to Goto
	void SetGoto() { m_state = State::Goto; }
	// Sets m_state to Select
	void SetSelect() { m_state = State::Select; }
	// Sets m_state to Buy
	void SetBuy() { m_state = State::Buy; }
	// Sets m_state to Sell
	void SetSell() { m_state = State::Sell; }

	// Returns true if m_state is set to GameOver, otherwise return false
	bool GetGameOver() const { return (m_state == State::GameOver) ? true : false; }
	// Returns true if m_state is set to Invalid, otherwise return false
	bool GetInvalid() const { return (m_state == State::Invalid) ? true : false; }
	// Returns true if m_state is set to Info, otherwise return false
	bool GetInfo() const { return (m_state == State::Info) ? true : false; }
	// Returns true if m_state is set to Help, otherwise return false
	bool GetHelp() const { return (m_state == State::Help) ? true : false; }
	// Returns true if m_state is set to EndDay, otherwise return false
	bool GetEndDay() const { return (m_state == State::EndDay) ? true : false; }
	// Returns true if the state is set to Goto, otherwise return false
	bool GetGoto() const { return (m_state == State::Goto) ? true : false; }
	// Returns true if m_state is set to Select, otherwise return false
	bool GetSelect() const { return (m_state == State::Select) ? true : false; }
	// Returns true if m_state is set to Buy, otherwise return false
	bool GetBuy() const { return (m_state == State::Buy) ? true : false; }
	// Returns true if m_state is set to Sell, otherwise return false
	bool GetSell() const { return (m_state == State::Sell) ? true : false; }

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
