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

	void Run();

private:
	bool Startup();
	bool Update();
	void DrawGraph();
	void DrawInfo();
	void DrawConsole();
	void UserInput();

	void InitialiseCompanies();
	bool StepDay();
	char GetDataFromArray(byte pHorizontal, byte pVertical);
	void BuySellFromCompany(int pAmount);
	string ConvertToCash(int pMoney);
	bool EndGame();
	void ResetGame();
	void SetInvalid(string pMessage);

	void ResetState() { m_state = State::Clear; }
	void SetGameOver() { m_state = State::GameOver; }
	void SetInfo() { m_state = State::Info; }
	void SetHelp() { m_state = State::Help; }
	void SetEndDay() { m_state = State::EndDay; }
	void SetGoto() { m_state = State::Goto; }
	void SetSelect() { m_state = State::Select; }
	void SetBuy() { m_state = State::Buy; }
	void SetSell() { m_state = State::Sell; }

	bool GetGameOver() const { return (m_state == State::GameOver) ? true : false; }
	bool GetInvalid() const { return (m_state == State::Invalid) ? true : false; }
	bool GetInfo() const { return (m_state == State::Info) ? true : false; }
	bool GetHelp() const { return (m_state == State::Help) ? true : false; }
	bool GetEndDay() const { return (m_state == State::EndDay) ? true : false; }
	bool GetGoto() const { return (m_state == State::Goto) ? true : false; }
	bool GetSelect() const { return (m_state == State::Select) ? true : false; }
	bool GetBuy() const { return (m_state == State::Buy) ? true : false; }
	bool GetSell() const { return (m_state == State::Sell) ? true : false; }

	State m_state = State::Info;	// Controls what the game should do
	byte m_selected = 0;			// The company currently selected for display
	bool m_bCloseApp = false;
	unsigned short m_day = 0;		// The current day
	unsigned short m_targetDay = 0;	// Used when fast forwarding
	unsigned int m_maxValue = 512;	// Scales the graph, doubles when exceeded
	int m_money = STARTINGCASH;		// The players cash
	string m_invalidMessage = "";	// A message to be printed in case of invalid input

	Company *m_companies;		// For creating companies on the heap
	unsigned int *m_dataRef;	// A local reference for the currently selected company data
};
