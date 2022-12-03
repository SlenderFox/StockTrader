#pragma once
#include "company.hpp"

class game
{
	gameState m_state = gameState::info;		// Controls what the game should do
	uint8 m_selected = 0;				// The company currently selected for display
	bool m_closeApp = false;
	uint16 m_day = 0;						// The current day
	uint16 m_targetDay = 0;				// Used when fast forwarding
	uint32 m_maxValue = 512;			// Scales the graph, doubles when exceeded
	int32 m_money = STARTINGCASH;		// The players cash
	std::string m_invalidMessage = "";		// A message to be printed in case of invalid input

	company *m_companies = nullptr;	// For creating companies on the heap

	bool startup() noexcept;
	bool update();
	void userInput();

	void initialiseCompanies() noexcept;
	bool stepDay() noexcept;
	void buySellFromCompany(int32 inAmount) noexcept;
	void resetGame() noexcept;
	void setInvalid(std::string inMessage) noexcept;

public:
	game() = default;
	~game();

	void run();
};
