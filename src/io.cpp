#include "io.hpp"
#include <iostream>

using std::cout;

namespace io
{
	void flush() noexcept
	{ cout.flush(); }

	void drawGraph(
		company* inCompanies,
		const uint8 inSelected,
		const uint32 inMaxValue
	) noexcept
	{
		// Prints currently selected company name
		cout << " " << inCompanies[inSelected].getName() << "\n";

		// Top edge of graph box
		cout << TOP_LEFT;
		for (uint8 i = 0; i < WIDTH - 2; i++)
		{ cout << HORIZONTAL; }
		cout << TOP_RIGHT << "\n";

		// Two for loops that print out the graph into the edge box
		for (uint8 y = 0; y < DETAIL; y++)
		{
			cout << VERTICAL;
			for (uint8 x = 0; x < WIDTH - 2; x++)
			{ cout << inCompanies[inSelected].getDataFromArray(inMaxValue, x, y); }
			cout << VERTICAL << "\n";
		}

		// Bottom edge of graph box
		cout << BOTTOM_LEFT;
		for (uint8 i = 0; i < WIDTH - 2; i++)
		{ cout << HORIZONTAL; }
		cout << BOTTOM_RIGHT << "\n";
	}

	void drawInfo(
		const company* inCompanies,
		const uint16 inDay,
		const int32 inMoney
	) noexcept
	{
		cout << " Day: " << inDay << "\n"
			<< " Money: " << convertToCash(inMoney) << "\n";

		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			cout << " " << inCompanies[i].getName() << ": "
				<< inCompanies[i].getOwnedStocks() << " @ "
				<< convertToCash(inCompanies[i].getCurrentValue()) << "\n";
		}

		//cout << " Max value: " << m_maxValue << "\n";

		//cout << "\n";
		for (uint16 i = 0; i < WIDTH; i++)
		{ cout << FLAT_LINE; }
		cout << "\n";
	}

	void drawConsole(
		const gameState inState,
		const std::string inInvalidMsg
	) noexcept
	{
		switch (inState)
		{
		case gameState::invalid:
			cout << " Command not accepted - Reason given:\n \"" << inInvalidMsg
				<< "\"\n Type 'help' for a list of accepted commands\n";
			break;
		case gameState::info:
			cout << "	Welcome to StockTrader!\n"
				<< " Your goal in this game is make the most amount of money\n"
				<< " in one year (365 days) by buying and selling stocks.\n"
				<< "	Type 'help' for commands\n";
			break;
		case gameState::help:
			cout << " Commands are:\n"
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

	bool endGame(
		const company* inCompanies,
		const int32 inMoney
	) noexcept
	{
		system("cls");

		cout << " Congratulations! You made it through 365 days, lets see how you did:\n\n";
		cout << " On hand money: " << convertToCash(inMoney)
			<< "\n Stocks in each company and how much they are worth: \n";

		uint32 totalCash = inMoney;

		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			cout << " " << inCompanies[i].getName() << ": "
				<< inCompanies[i].getOwnedStocks() << " @ "
				<< convertToCash(inCompanies[i].getCurrentValue()) << "\n";

			totalCash += inCompanies[i].getOwnedStocks() * inCompanies[i].getCurrentValue();
		}

		cout << " All for a total of: " << convertToCash(totalCash) << "\n";
		cout << "\n Do you want to play again? [y/n] ";
		cout.flush();

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

	std::string convertToCash(int32 inMoney) noexcept
	{
		std::string moneyText = std::to_string(inMoney);
		std::string temp;

		// Reverse the string, placing a comma after every third number
		for (int32 i = (int32)moneyText.length() - 1, j = 0; i >= 0; --i, ++j)
		{
			if (j != 0 && j % 3 == 0)
			{ temp += ","; }
			temp += moneyText[i];
		}

		temp += "$";
		moneyText = "";

		// Reverse the string again
		for (int32 i = (int32)temp.length() - 1; i >= 0; --i)
		{ moneyText += temp[i]; }

		return moneyText;
	}
}
