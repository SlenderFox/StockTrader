#include "game.hpp"
//#include "winclude.hpp"
#include <random>
#include <time.h>
#include <sstream>
#include <iostream>
#include <string.h>

using std::cout;
using std::cin;

namespace stockTrader
{
	game::~game()
	{ delete[] m_companies; }

	void game::run()
	{
		if (!startup())
			return;

		// This loop allows for the game to be played multiple times
		while (!m_closeApp)
		{
			while (update()) {}

			if (!endGame())
				resetGame();
			else
				m_closeApp = true;
		}
	}

	bool game::startup() noexcept
	{
		// TODO: Don't use
		srand((unsigned int)time(nullptr));

		//if (!MoveWindow(GetConsoleWindow(), 50, 50, (int)(WIDTH * CHARWIDTH + 33), 900, TRUE))
			return false;

		// Initialises the companies and player
		initialiseCompanies();

		// Returns true if startup was successful
		return true;
	}

	void game::initialiseCompanies() noexcept
	{
		// Creates 5 new empty companies
		m_companies = new company[NUMCOMPANIES];

		// Initialises each company
		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			// Temp for testing
			switch (i)
			{
			default:
			case 0:
				m_companies[i].initialiseCompany(companyType::flat, "Flat", 100);
				break;
			case 1:
				m_companies[i].initialiseCompany(companyType::growth, "Growth", 100);
				break;
			case 2:
				m_companies[i].initialiseCompany(companyType::upAndDown, "UpNDown", 100);
				break;
			case 3:
				m_companies[i].initialiseCompany(companyType::falseHope, "FalseHope", 100);
				break;
			case 4:
				m_companies[i].initialiseCompany(companyType::twinPeaks, "TwinPeaks", 100);
				break;
			}
		}

		// Sets default selected company
		m_selected = 0;
	}

	bool game::update()
	{
		if (!stepDay())
			return false;

		// TODO: Look into
		// Clears the console
		system("cls");
		// Draw the graph of the currently selected company
		drawGraph();
		// Draw current game info
		drawInfo();
		// Draw the in-game console
		drawConsole();
		cout.flush();

		// Asks the user for input
		if (m_state != gameState::gotoDay)
			userInput();

		return true;
	}

	bool game::stepDay() noexcept
	{
		// Makes sure that the user wants the day to end
		if (m_state == gameState::endDay || m_state == gameState::gotoDay)
		{
			m_day++;
			// Ends game when year ends
			if (m_day == 366)
			{
				m_state = gameState::gameOver;
				// Currently the program just ends
				return false;
			}
			for (uint8 i = 0; i < NUMCOMPANIES; i++)
			{
				// Updates the data array for each company
				m_companies[i].updateCompanyValue(-0.05f, 0.06f);
				if (m_companies[i].getCurrentValue() > m_maxValue)
					m_maxValue <<= 1;
			}

			// If goto has been called and target day has not been reached, prevent state from 	being reset
			if (m_state == gameState::gotoDay && m_day != m_targetDay)
				return true;

			m_state = gameState::clear;
		}
		return true;
	}

	void game::userInput()
	{
		m_state = gameState::clear;

		// Ready for player input
		char input[50] = "\0";
		cout << ">";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> input;

		// Input loop
		while (true)
		{
			// TODO: Remove strcmp

			// Display all commands
			if (strcmp(input, "help") == 0)
			{
				m_state = gameState::help;
				return;
			}

			// End current day and move to the next
			if (strcmp(input, "end") == 0 ||
				strcmp(input, "next") == 0 ||
				strcmp(input, "n") == 0)
			{
				m_state = gameState::endDay;
				return;
			}

			switch (m_state)
			{
			case gameState::gotoDay:
				// After invoking the fast forward command, process input as number
				try
				{
					std::string num = input;
					int32 val = std::stoi(num);
					if (val < m_day)
						break;
					else if (val > 365)
						break;
					m_targetDay = val;
					return;
				}
				catch (const std::exception &e) { throw e; }
				break;
			case gameState::select:
				// After invoking the select command, searches for a valid request
				try
				{
					std::string num = input;
					int32 val = std::stoi(num);
					if (val < 1)
						val = 1;
					else if (val > (int32)NUMCOMPANIES)
						val = (int32)NUMCOMPANIES;
					m_selected = val - 1;
					return;
				}
				catch (const std::exception &e) { throw e; }
				break;
			case gameState::buy:
				// After invoking the buy command, process input as number
				try
				{
					std::string num = input;
					int32 val = std::stoi(num);
					if (val < 0)
						val = 0;
					else if (val > MAXTRANSFER)
						val = MAXTRANSFER;
					buySellFromCompany(val);
					return;
				}
				catch (const std::exception &e) { throw e; }
				break;
			case gameState::sell:
				// After invoking the sell command, process input as number
				try
				{
					std::string num = input;
					int32 val = std::stoi(num);
					if (val < 0)
						val = 0;
					else if (val > MAXTRANSFER)
						val = MAXTRANSFER;
					buySellFromCompany(-val);
					return;
				}
				catch (const std::exception &e) { throw e; }
				break;
			default:
				break;
			}

			// Primes the fast forward command
			if (strcmp(input, "goto") == 0) { m_state = gameState::gotoDay; }
			// Primes the select command
			if (strcmp(input, "select") == 0) { m_state = gameState::select; }
			// Primes the buy command
			if (strcmp(input, "buy") == 0) { m_state = gameState::buy; }
			// Primes the sell command
			if (strcmp(input, "sell") == 0) { m_state = gameState::sell; }

			char next = cin.peek();
			if (next == '\n' || next == EOF)
				break;
			for (uint16 i = 0; i < 50; i++)
			{
				input[i] = '\0';
			}
			cin >> input;
		}

		// Failed input handling
		if (m_state == gameState::gotoDay) { setInvalid("Invalid value entered, please enter a number between today and 365"); }
		else if (m_state == gameState::select) { setInvalid("Invalid value entered"); }
		else if (m_state == gameState::buy) { setInvalid("Invalid value entered"); }
		else if (m_state == gameState::sell) { setInvalid("Invalid value entered"); }
		else { setInvalid("Command not found"); }
		cout.flush();
		return;
	}

	void game::drawGraph() noexcept
	{
		// Prints currently selected company name
		cout << " " << m_companies[m_selected].getName() << "\n";

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
			{ cout << m_companies[m_selected].getDataFromArray(m_maxValue, x, y); }
			cout << VERTICAL << "\n";
		}

		// Bottom edge of graph box
		cout << BOTTOM_LEFT;
		for (uint8 i = 0; i < WIDTH - 2; i++)
		{ cout << HORIZONTAL; }
		cout << BOTTOM_RIGHT << "\n";
	}

	void game::drawInfo() noexcept
	{
		cout << " Day: " << m_day << "\n"
			<< " Money: " << convertToCash(m_money) << "\n";

		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			cout << " " << m_companies[i].getName() << ": "
				<< m_companies[i].getOwnedStocks() << " @ "
				<< convertToCash(m_companies[i].getCurrentValue()) << "\n";
		}

		//cout << " Max value: " << m_maxValue << "\n";

		//cout << "\n";
		for (uint16 i = 0; i < WIDTH; i++)
		{ cout << FLAT_LINE; }
		cout << "\n";
	}

	void game::drawConsole() noexcept
	{
		switch (m_state)
		{
		case gameState::invalid:
			cout << " Command not accepted - Reason given:\n \"" << m_invalidMessage
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

	bool game::endGame() noexcept
	{
		system("cls");

		cout << " Congratulations! You made it through 365 days, lets see how you did:\n\n";
		cout << " On hand money: " << convertToCash(m_money)
			<< "\n Stocks in each company and how much they are worth: \n";

		uint32 totalCash = m_money;

		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			cout << " " << m_companies[i].getName() << ": "
				<< m_companies[i].getOwnedStocks() << " @ "
				<< convertToCash(m_companies[i].getCurrentValue()) << "\n";

			totalCash += m_companies[i].getOwnedStocks() * m_companies[i].getCurrentValue();
		}

		cout << " All for a total of: " << convertToCash(totalCash) << "\n";
		cout << "\n Do you want to play again? [y/n] ";
		cout.flush();

		// Ready for player input
		char input[50] = "\0";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> input;

		// Treat any response other than "y" as no
		if (std::string(input) == "y")
			return false;

		return true;
	}

	std::string game::convertToCash(const int32 m_money) noexcept
	{
		std::string moneyText = std::to_string(m_money);
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

	void game::resetGame() noexcept
	{
		m_state = gameState::info;
		m_day = 0;
		m_targetDay = 0;
		m_maxValue = 512;
		m_money = STARTINGCASH;

		initialiseCompanies(); // Sets m_selected to 0
	}

	void game::buySellFromCompany(int32 inAmount) noexcept
	{
		// inAmount will be positive to buy and negative to sell
		if (m_companies[m_selected].getOwnedStocks() + inAmount >= 0)
		{
			uint32 cost = inAmount * m_companies[m_selected].getCurrentValue();
			if (m_money - cost >= 0)
			{
				m_money -= cost;
				m_companies[m_selected].modifyOwnedStocks(inAmount);
			}
			else
			{
				// Upgrade this message to show the max you can buy
				uint32 max = m_money / m_companies[m_selected].getCurrentValue();
				setInvalid("You can only afford to buy " + std::to_string(max) + " stocks in " + m_companies[m_selected].getName());
			}
		}
		else
		{
			setInvalid("You can't sell more stocks than you currently own");
		}
	}

	void game::setInvalid(std::string inMessage) noexcept
	{
		m_state = gameState::invalid;
		m_invalidMessage = inMessage;
	}
}
