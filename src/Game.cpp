#pragma region
#include "Game.hpp"
#include <iostream>
#include <Windows.h>
#include <random>
#include <time.h>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
#pragma endregion

Game::~Game()
{
	delete[] m_companies;
}

void Game::Run()
{
	if (!Startup())
		return;

	// This loop allows for the game to be played multiple times
	while (!m_closeApp)
	{
		while (Update()) {}

		if (!EndGame())
			ResetGame();
		else
			m_closeApp = true;
	}
}

bool Game::Startup() noexcept
{
	srand((unsigned int)time(nullptr));
	if (!MoveWindow(GetConsoleWindow(), 50, 50, (int)(WIDTH * CHARWIDTH + 33), 900, TRUE))
		return false;

	// Initialises the companies and player
	InitialiseCompanies();

	// Returns true if startup was successful
	return true;
}

void Game::InitialiseCompanies() noexcept
{
	// Creates 5 new empty companies
	m_companies = new Company[NUMCOMPANIES];

	// Initialises each company
	for (uint8 i = 0; i < NUMCOMPANIES; i++)
	{
		// Temp for testing
		switch (i)
		{
		default:
		case 0:
			m_companies[i].InitialiseCompany(CompanyType::Flat, "Flat", 100);
			break;
		case 1:
			m_companies[i].InitialiseCompany(CompanyType::Growth, "Growth", 100);
			break;
		case 2:
			m_companies[i].InitialiseCompany(CompanyType::UpNDown, "UpNDown", 100);
			break;
		case 3:
			m_companies[i].InitialiseCompany(CompanyType::FalseHope, "FalseHope", 100);
			break;
		case 4:
			m_companies[i].InitialiseCompany(CompanyType::TwinPeaks, "TwinPeaks", 100);
			break;
		}
	}

	// Sets default selected company
	m_selected = 0;
}

bool Game::Update()
{
	if (!StepDay())
		return false;

	// Clears the console
	system("cls");
	// Draw the graph of the currently selected company
	DrawGraph();
	// Draw current game info
	DrawInfo();
	// Draw the in-game console
	DrawConsole();

	// Asks the user for input
	if (!GetGoto())
		UserInput();

	return true;
}

bool Game::StepDay() noexcept
{
	// Makes sure that the user wants the day to end
	if (GetEndDay() || GetGoto())
	{
		m_day++;
		// Ends game when year ends
		if (m_day == 366)
		{
			SetGameOver();
			// Currently the program just ends
			return false;
		}
		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			// Updates the data array for each company
			m_companies[i].UpdateCompanyValue(-0.04f, 0.07f);
			if (m_companies[i].GetCurrentValue() > m_maxValue)
				m_maxValue <<= 1;
		}

		// If goto has been called and target day has not been reached, prevent state from being reset
		if (GetGoto() && m_day != m_targetDay)
			return true;

		ResetState();
	}
	return true;
}

void Game::DrawGraph() noexcept
{
	// Prints currently selected company name
	cout << " " << m_companies[m_selected].GetName() << endl;

	// Top edge of graph box
	cout << TOP_LEFT;
	for (uint8 i = 0; i < WIDTH - 2; i++)
	{
		cout << HORIZONTAL;
	}
	cout << TOP_RIGHT;

	// Two for loops that print out the graph into the edge box
	for (uint8 y = 0; y < DETAIL; y++)
	{
		cout << VERTICAL;
		for (uint8 x = 0; x < WIDTH - 2; x++)
		{
			cout << GetDataFromArray(&m_companies[m_selected], x, y);
		}
		cout << VERTICAL;
	}

	// Bottom edge of graph box
	cout << BOTTOM_LEFT;
	for (uint8 i = 0; i < WIDTH - 2; i++)
	{
		cout << HORIZONTAL;
	}
	cout << BOTTOM_RIGHT << endl;
}

void Game::DrawInfo() noexcept
{
	cout << " Day: " << m_day << endl;
	cout << " Money: " << ConvertToCash(m_money) << endl;

	for (uint8 i = 0; i < NUMCOMPANIES; i++)
	{
		cout << " " << m_companies[i].GetName() << ": "
			<< m_companies[i].GetOwnedStocks() << " @ "
			<< ConvertToCash(m_companies[i].GetCurrentValue()) << endl;
	}

	//cout << " Max value: " << m_maxValue << endl;

	//cout << endl;
	for (uint16 i = 0; i < WIDTH; i++)
	{
		cout << FLAT_LINE;
	}
	cout << endl;
}

void Game::DrawConsole() noexcept
{
	if (GetInvalid())
		cout << " Command not accepted - Reason given:\n \"" << m_invalidMessage
		<< "\"\n Type 'help' for a list of accepted commands" << endl;

	if (GetInfo())
		cout << "	Welcome to StockTrader!\n"
		<< " Your goal in this game is make the most amount of money\n"
		<< " in one year (365 days) by buying and selling stocks.\n"
		<< "	Type 'help' for commands" << endl;

	if (GetHelp())
	{
		cout << " Commands are:\n"
			<< " 'help'               | Lists these commands\n"
			<< " 'end day'/'next'/'n' | Ends current day and moves on to the next\n"
			<< " 'goto <integer>'     | Skips ahead to specified day (today-365)\n"
			<< " 'select <integer>'   | Chooses the current company to be displayed\n"
			<< " 'buy <integer>'      | Attempts to buy stocks of the selected company\n"
			<< " 'sell <integer>'     | Attempts to sell stocks of the selected company\n\n"
			<< " NOTE: All commands are lower case." << endl;
	}
}

void Game::UserInput()
{
	ResetState();

	// Ready for player input
	char input[50] = "\0";
	cout << ">";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> input;

	// Input loop
	while (input)
	{
		// TODO: Remove strcmp

		// Display all commands
		if (strcmp(input, "help") == 0)
		{
			SetHelp();
			return;
		}

		// End current day and move to the next
		if (strcmp(input, "end") == 0 ||
			strcmp(input, "next") == 0 ||
			strcmp(input, "n") == 0)
		{
			SetEndDay();
			return;
		}

		switch (m_state)
		{
		case State::Goto:
			// After invoking the fast forward command, process input as number
			try
			{
				string num = input;
				int32 val = std::stoi(num);
				if (val < m_day)
					break;
				else if (val > 365)
					break;
				m_targetDay = val;
				return;
			}
			catch (const std::exception& e) { throw e; }
			break;
		case State::Select:
			// After invoking the select command, searches for a valid request
			try
			{
				string num = input;
				int32 val = std::stoi(num);
				if (val < 1)
					val = 1;
				else if (val > NUMCOMPANIES)
					val = NUMCOMPANIES;
				m_selected = val - 1;
				return;
			}
			catch (const std::exception& e) { throw e; }
			break;
		case State::Buy:
			// After invoking the buy command, process input as number
			try
			{
				string num = input;
				int32 val = std::stoi(num);
				if (val < 0)
					val = 0;
				else if (val > MAXTRANSFER)
					val = MAXTRANSFER;
				BuySellFromCompany(val);
				return;
			}
			catch (const std::exception& e) { throw e; }
			break;
		case State::Sell:
			// After invoking the sell command, process input as number
			try
			{
				string num = input;
				int32 val = std::stoi(num);
				if (val < 0)
					val = 0;
				else if (val > MAXTRANSFER)
					val = MAXTRANSFER;
				BuySellFromCompany(-val);
				return;
			}
			catch (const std::exception& e) { throw e; }
			break;
		default:
			break;
		}

		// Primes the fast forward command
		if (strcmp(input, "goto") == 0) { SetGoto(); }
		// Primes the select command
		if (strcmp(input, "select") == 0) { SetSelect(); }
		// Primes the buy command
		if (strcmp(input, "buy") == 0) { SetBuy(); }
		// Primes the sell command
		if (strcmp(input, "sell") == 0) { SetSell(); }

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
	if (GetGoto()) { SetInvalid("Invalid value entered, please enter a number between today and 365"); }
	else if (GetSelect()) { SetInvalid("Invalid value entered"); }
	else if (GetBuy()) { SetInvalid("Invalid value entered"); }
	else if (GetSell()) { SetInvalid("Invalid value entered"); }
	else { SetInvalid("Command not found"); }
	return;
}

bool Game::EndGame() noexcept
{
	system("cls");

	cout << " Congratulations! You made it through 365 days, lets see how you did:\n" << endl;

	cout << " On hand money: " << ConvertToCash(m_money)
		<< "\n Stocks in each company and how much they are worth: " << endl;

	uint32 totalCash = m_money;

	for (uint8 i = 0; i < NUMCOMPANIES; i++)
	{
		cout << " " << m_companies[i].GetName() << ": "
			<< m_companies[i].GetOwnedStocks() << " @ "
			<< ConvertToCash(m_companies[i].GetCurrentValue()) << endl;

		totalCash += m_companies[i].GetOwnedStocks() * m_companies[i].GetCurrentValue();
	}

	cout << " All for a total of: " << ConvertToCash(totalCash) << endl;

	cout << "\n Do you want to play again? [y/n] ";

	// Ready for player input
	char input[50] = "\0";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> input;

	if (strcmp(input, "y") == 0)
		return false;	// Do not end the game
	if (strcmp(input, "n") == 0)
		return true;	// End the game

	// Fix C4715
	return true;
}

void Game::ResetGame() noexcept
{
	SetInfo();
	m_day = 0;
	m_targetDay = 0;
	m_maxValue = 512;
	m_money = STARTINGCASH;

	InitialiseCompanies();	// Sets m_selected to 0
}

char Game::GetDataFromArray(
	Company* pComp,
	const uint8 pHorizontal,
	uint8 pVertical) noexcept
{
	// The lines are drawn between the values
	// (Should be from 0 to DETAIL-1 but done this way to prevent clipping)
	// Inverts vertical from DETAIL-1 to 0 to 0 to DETAIL
	pVertical = DETAIL - pVertical;
	// 0 to m_maxValue value is scaled to 0 to DETAIL
	uint32 leftValue = (uint32)(pComp->GetCompanyData()[WIDTH - 2 - pHorizontal] / (float)(m_maxValue / DETAIL));
	uint32 rightValue = (uint32)(pComp->GetCompanyData()[WIDTH - 3 - pHorizontal] / (float)(m_maxValue / DETAIL));

	if (pComp->GetCompanyData()[WIDTH - 2 - pHorizontal] == NULL)
		return ' ';
	else if (leftValue == pVertical && leftValue == rightValue)
		return '_';
	else if (leftValue == pVertical && leftValue < rightValue)
		return '/';
	else if (leftValue == pVertical + 1 && leftValue > rightValue)
		return '\\';
	else
		return ' ';
}

string Game::ConvertToCash(int32 pMoney) noexcept
{
	string moneyText = to_string(pMoney);
	string temp;

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

void Game::BuySellFromCompany(int32 pAmount) noexcept
{
	// pAmount will be positive to buy and negative to sell
	if (m_companies[m_selected].GetOwnedStocks() + pAmount >= 0)
	{
		uint32 cost = pAmount * m_companies[m_selected].GetCurrentValue();
		if (m_money - cost >= 0)
		{
			m_money -= cost;
			m_companies[m_selected].ModifyOwnedStocks(pAmount);
		}
		else
		{
			// Upgrade this message to show the max you can buy
			uint32 max = m_money / m_companies[m_selected].GetCurrentValue();
			SetInvalid("You can only afford to buy " + to_string(max) + " stocks in " + m_companies[m_selected].GetName());
		}
	}
	else
	{
		SetInvalid("You can't sell more stocks than you currently own");
	}
}

void Game::SetInvalid(string pMessage) noexcept
{
	m_state = State::Invalid;
	m_invalidMessage = pMessage;
}
