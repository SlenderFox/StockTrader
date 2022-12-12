#pragma once
#include "company.hpp"

namespace stockTrader
{
	class game
	{
		bool m_closeApp = false;
		// Controls what the game should do
		gameState m_state = gameState::info;
		// The company currently selected for display
		uint8 m_selected = 0;
		uint16 m_day = 0;
		// Used when fast forwarding
		uint16 m_targetDay = 0;
		// Scales the graph, doubles when exceeded
		uint32 m_maxValue = 512;
		int32 m_money = STARTINGCASH;
		// A message to be printed in case of invalid input
		std::string m_invalidMessage = "";
		// For creating companies on the heap
		company *m_companies = nullptr;

		bool startup() noexcept;
		bool update();
		void userInput();

		void drawGraph() noexcept;
		void drawInfo() noexcept;
		void drawConsole() noexcept;
		_NODISCARD bool endGame() noexcept;

		_NODISCARD std::string convertToCash(const int32 inMoney) noexcept;
		void initialiseCompanies() noexcept;
		bool stepDay() noexcept;
		void buySellFromCompany(int32 inAmount) noexcept;
		void resetGame() noexcept;
		void setInvalid(std::string inMessage) noexcept;
		void clear() noexcept;

	public:
		game() = default;
		~game();

		void run();
	};
}
