#pragma once
#include "Company.hpp"

class Game
{
	State m_state = State::Info;		// Controls what the game should do
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
	void DrawGraph() noexcept;
	void DrawInfo() noexcept;
	void DrawConsole() noexcept;
	void UserInput();

	void InitialiseCompanies() noexcept;
	bool StepDay() noexcept;
	char GetDataFromArray(
		Company *pComp,
		const uint8 pHorizontal,
		uint8 pVertical
	) noexcept;
	void BuySellFromCompany(int32 pAmount) noexcept;
	string ConvertToCash(int32 pMoney) noexcept;
	bool EndGame() noexcept;
	void ResetGame() noexcept;
	void SetInvalid(string pMessage) noexcept;

	void ResetState() noexcept;
	void SetGameOver() noexcept;
	void SetInfo() noexcept;
	void SetHelp() noexcept;
	void SetEndDay() noexcept;
	void SetGoto() noexcept;
	void SetSelect() noexcept;
	void SetBuy() noexcept;
	void SetSell() noexcept;

	bool GetGameOver() const noexcept;
	bool GetInvalid() const noexcept;
	bool GetInfo() const noexcept;
	bool GetHelp() const noexcept;
	bool GetEndDay() const noexcept;
	bool GetGoto() const noexcept;
	bool GetSelect() const noexcept;
	bool GetBuy() const noexcept;
	bool GetSell() const noexcept;

public:
	Game() = default;
	~Game();

	void Run();
};
