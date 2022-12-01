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

	Company* m_companies = nullptr;	// For creating companies on the heap

private:
	bool Startup() noexcept;
	bool Update();
	void DrawGraph() noexcept;
	void DrawInfo() noexcept;
	void DrawConsole() noexcept;
	void UserInput();

	void InitialiseCompanies() noexcept;
	bool StepDay() noexcept;
	char GetDataFromArray(
		Company* pComp,
		const uint8 pHorizontal,
		uint8 pVertical) noexcept;
	void BuySellFromCompany(int32 pAmount) noexcept;
	string ConvertToCash(int32 pMoney) noexcept;
	bool EndGame() noexcept;
	void ResetGame() noexcept;
	void SetInvalid(string pMessage) noexcept;

	void ResetState() noexcept	 { m_state = State::Clear;		}
	void SetGameOver() noexcept { m_state = State::GameOver;	}
	void SetInfo() noexcept		 { m_state = State::Info;		}
	void SetHelp() noexcept		 { m_state = State::Help;		}
	void SetEndDay() noexcept	 { m_state = State::EndDay;	}
	void SetGoto() noexcept		 { m_state = State::Goto;		}
	void SetSelect() noexcept	 { m_state = State::Select;	}
	void SetBuy() noexcept		 { m_state = State::Buy;		}
	void SetSell() noexcept		 { m_state = State::Sell;		}

	bool GetGameOver() const noexcept { return (m_state == State::GameOver)	? true : false; }
	bool GetInvalid() const noexcept	 { return (m_state == State::Invalid)	? true : false; }
	bool GetInfo() const noexcept		 { return (m_state == State::Info)		? true : false; }
	bool GetHelp() const noexcept 	 { return (m_state == State::Help)		? true : false; }
	bool GetEndDay() const noexcept	 { return (m_state == State::EndDay)	? true : false; }
	bool GetGoto() const noexcept		 { return (m_state == State::Goto)		? true : false; }
	bool GetSelect() const noexcept	 { return (m_state == State::Select)	? true : false; }
	bool GetBuy() const noexcept		 { return (m_state == State::Buy)		? true : false; }
	bool GetSell() const noexcept		 { return (m_state == State::Sell)		? true : false; }

public:
	Game() {}
	~Game();

	void Run();
};
