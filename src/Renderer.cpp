#include "Renderer.hpp"
#include <iostream>

namespace Renderer
{
	void DrawGraph(
		Company* inCompanies,
		const uint8 inSelected,
		const uint32 inMaxValue
	) noexcept
	{
		// Prints currently selected company name
		std::cout << " " << inCompanies[inSelected].GetName() << "\n";

		// Top edge of graph box
		std::cout << TOP_LEFT;
		for (uint8 i = 0; i < WIDTH - 2; i++)
		{
			std::cout << HORIZONTAL;
		}
		std::cout << TOP_RIGHT << "\n";

		// Two for loops that print out the graph into the edge box
		for (uint8 y = 0; y < DETAIL; y++)
		{
			std::cout << VERTICAL;
			for (uint8 x = 0; x < WIDTH - 2; x++)
			{
				std::cout << inCompanies[inSelected].GetDataFromArray(inMaxValue, x, y);
			}
			std::cout << VERTICAL << "\n";
		}

		// Bottom edge of graph box
		std::cout << BOTTOM_LEFT;
		for (uint8 i = 0; i < WIDTH - 2; i++)
		{
			std::cout << HORIZONTAL;
		}
		std::cout << BOTTOM_RIGHT << "\n";
	}

	void DrawInfo(
		const Company* inCompanies,
		const uint16 inDay,
		const int32 inMoney
	) noexcept
	{
		std::cout << " Day: " << inDay << "\n"
			<< " Money: " << ConvertToCash(inMoney) << "\n";

		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			std::cout << " " << inCompanies[i].GetName() << ": "
				<< inCompanies[i].GetOwnedStocks() << " @ "
				<< ConvertToCash(inCompanies[i].GetCurrentValue()) << "\n";
		}

		//cout << " Max value: " << m_maxValue << "\n";

		//cout << "\n";
		for (uint16 i = 0; i < WIDTH; i++)
		{
			std::cout << FLAT_LINE;
		}
		std::cout << "\n";
	}

	void DrawConsole(
		const Game::State inState,
		const std::string inInvalidMsg
	) noexcept
	{
		switch (inState)
		{
		case Game::State::Invalid:
			std::cout << " Command not accepted - Reason given:\n \"" << inInvalidMsg
				<< "\"\n Type 'help' for a list of accepted commands\n";
			break;
		case Game::State::Info:
			std::cout << "	Welcome to StockTrader!\n"
				<< " Your goal in this game is make the most amount of money\n"
				<< " in one year (365 days) by buying and selling stocks.\n"
				<< "	Type 'help' for commands\n";
			break;
		case Game::State::Help:
			std::cout << " Commands are:\n"
				<< " 'help'               | Lists these commands\n"
				<< " 'end day'/'next'/'n' | Ends current day and moves on to the next\n"
				<< " 'goto <integer>'     | Skips ahead to specified day (today-365)\n"
				<< " 'select <integer>'   | Chooses the current company to be displayed\n"
				<< " 'buy <integer>'      | Attempts to buy stocks of the selected company\n"
				<< " 'sell <integer>'     | Attempts to sell stocks of the selected company\n\n"
				<< " NOTE: All commands are lower case.\n";
			break;
		default: break;
		}
	}

	bool EndGame(
		const Company* inCompanies,
		const int32 inMoney
	) noexcept
	{
		system("cls");

		std::cout << " Congratulations! You made it through 365 days, lets see how you did:\n\n";
		std::cout << " On hand money: " << ConvertToCash(inMoney)
			<< "\n Stocks in each company and how much they are worth: \n";

		uint32 totalCash = inMoney;

		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			std::cout << " " << inCompanies[i].GetName() << ": "
				<< inCompanies[i].GetOwnedStocks() << " @ "
				<< ConvertToCash(inCompanies[i].GetCurrentValue()) << "\n";

			totalCash += inCompanies[i].GetOwnedStocks() * inCompanies[i].GetCurrentValue();
		}

		std::cout << " All for a total of: " << ConvertToCash(totalCash) << "\n";
		std::cout << "\n Do you want to play again? [y/n] ";
		std::cout.flush();

		// Ready for player input
		char input[50] = "\0";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> input;

		// Treat any response other than "y" as no
		if (std::string(input) == "y")
			return false;

		return true;
	}

	std::string ConvertToCash(int32 pMoney) noexcept
	{
		std::string moneyText = std::to_string(pMoney);
		std::string temp;

		// Reverse the string, placing a comma after every third number
		for (int32 i = (int32)moneyText.length() - 1, j = 0; i >= 0; --i, ++j)
		{
			if (j != 0 && j % 3 == 0)
				temp += ",";
			temp += moneyText[i];
		}

		temp += "$";
		moneyText = "";

		// Reverse the string again
		for (int32 i = (int32)temp.length() - 1; i >= 0; --i)
		{
			moneyText += temp[i];
		}

		return moneyText;
	}
}
