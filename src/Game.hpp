#pragma once
#include "Company.hpp"
#include "Enums.hpp"

class Game
{
	GameState m_state = GameState::Info;		// Controls what the game should do
	uint8 m_selected = 0;				// The company currently selected for display
	bool m_closeApp = false;
	uint16 m_day = 0;						// The current day
	uint16 m_targetDay = 0;				// Used when fast forwarding
	uint32 m_maxValue = 512;			// Scales the graph, doubles when exceeded
	int32 m_money = STARTINGCASH;		// The players cash
	string m_invalidMessage = "";		// A message to be printed in case of invalid input

	Company *m_companies = nullptr;	// For creating companies on the heap

	bool Startup() noexcept;
	bool Update();
	void UserInput();

	void InitialiseCompanies() noexcept;
	bool StepDay() noexcept;
	void BuySellFromCompany(int32 pAmount) noexcept;
	void ResetGame() noexcept;
	void SetInvalid(string pMessage) noexcept;

public:
	Game() = default;
	~Game();

	void Run();
};
