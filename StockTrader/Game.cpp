/*------------------------------------------------------
	File Name: Game.cpp
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)
------------------------------------------------------*/

#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <random>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

bool Game::Startup()
{
	srand((unsigned int)time(nullptr));
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 0, 0 , (WIDTH * 8 + 33), 900};
	// 80-673
	// 100-833
	MoveWindow(hwnd, rect.top, rect.left, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	// Initialises the companies and player
	if (!InitialiseCompanies())
		return false;

	// Returns true if startup was successful
	return true;
}

void Game::Update()
{
	StepDay();
	UpdateMaxValue();

	// Ends game when year ends
	if (m_currentDay == 366)
	{
		SetGameOver(true);
		return;
	}
}

void Game::Draw()
{
	system("cls");

	// Print the title and short description of game
	DrawHeader();

	// Print out info about the currently selected company
	DrawGraph();

	// Print out info about the player
	DrawInfo();
}

void Game::UserInput()
{
	ClearBitData();

	switch (GetCommand())
	{
	case HELP:
		SetHelp(true);
		break;
	case ENDDAY:
		SetEndDay(true);
		break;
	case FASTFORWARD:
		GotoDay(m_targetDay);
		break;
	case BUY:
		break;
	case SELL:
		break;
	case SELECT_ONE:
		m_currentlySelected = 0;
		break;
	case SELECT_TWO:
		m_currentlySelected = 1;
		break;
	case SELECT_THREE:
		m_currentlySelected = 2;
		break;
	case SELECT_FOUR:
		m_currentlySelected = 3;
		break;
	case SELECT_FIVE:
		m_currentlySelected = 4;
		break;
	case INVALID:
	default:
		SetInvalid(true);
		break;
	}
}

bool Game::InitialiseCompanies()
{
	// Creates 5 new empty companies
	m_companies = new Companies[COMPAMOUNT];

	// Initialises each company
	for (int i = 0; i < COMPAMOUNT; i++)
	{
		// Temp for testing
		switch (i)
		{
		default:
		case 0:
			m_companies[i].InitializeCompany(CompanyType::FLAT, "Flat", 20);
			break;
		case 1:
			m_companies[i].InitializeCompany(CompanyType::GROWTH, "Growth", 20);
			break;
		case 2:
			m_companies[i].InitializeCompany(CompanyType::UPNDOWN, "UpNDown", 20);
			break;
		case 3:
			m_companies[i].InitializeCompany(CompanyType::FALSEHOPE, "FalseHope", 20);
			break;
		case 4:
			m_companies[i].InitializeCompany(CompanyType::TWINPEAKS, "TwinPeaks", 20);
			break;
		}
	}

	// Sets default selected company
	m_currentlySelected = 0;

	return true;
}

void Game::StepDay()
{
	// Makes sure that the user wants the day to end
	if (GetEndDay())
	{
		for (int i = 0; i < 5; i++)
		{
			// Updates the data array for each company
			m_companies[i].UpdateCompanyValue(-5, 20);
		}

		m_currentDay++;
		SetEndDay(false);
	}
}

void Game::GotoDay(short pTargetDay)
{
	if (pTargetDay <= m_currentDay)
		return;

	// Continually steps through the days until the target day is reached
	while (m_currentDay < pTargetDay)
	{
		SetEndDay(true);
		StepDay();
	}
}

byte Game::GetCommand()
{
	// Ready for player input
	bool bSelect = false;
	bool bFastForward = false;
	char input[50] = "\0";
	cout << ">";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> input;

	// Input loop
	while (input)
	{
		// Display all commands
		if (strcmp(input, "help") == 0)
			return HELP;

		// End current day and move to the next
		if (strcmp(input, "end") == 0 ||
			strcmp(input, "next") == 0 ||
			strcmp(input, "n") == 0)
		{
			return ENDDAY;
		}

		// After invoking the fast forward command, process as number
		if (bFastForward)
		{
			// Initialises a char array
			short targetDay[3] = { 0 };
			if (input[1] != '\0')
			{
				if (input[2] != '\0')
				{
					// Means number is triple digit
					targetDay[0] = input[2];	//Ones
					targetDay[1] = input[1];	//Tens
					targetDay[2] = input[0];	//Hundreds

					targetDay[0] -= 48;
					targetDay[1] -= 48;
					targetDay[2] -= 48;
				}
				else
				{
					// Means nunber is double digit
					targetDay[0] = input[1];	//Ones
					targetDay[1] = input[0];	//Tens

					targetDay[0] -= 48;
					targetDay[1] -= 48;
				}
			}
			else
			{
				// Means number is single digit
				targetDay[0] = input[0];		//Ones
				targetDay[0] -= 48;
			}

			FormInt(targetDay);
			return FASTFORWARD;
		}

		// After invoking the select command, searches for a valid request
		if (bSelect)
		{
			if (strcmp(input, "one") == 0 ||
				strcmp(input, "1") == 0 ||
				strcmp(input, "flat") == 0)
				return SELECT_ONE;

			if (strcmp(input, "two") == 0 ||
				strcmp(input, "2") == 0 ||
				strcmp(input, "growth") == 0)
				return SELECT_TWO;

			if (strcmp(input, "three") == 0 ||
				strcmp(input, "3") == 0 ||
				strcmp(input, "upndown") == 0)
				return SELECT_THREE;

			if (strcmp(input, "four") == 0 ||
				strcmp(input, "4") == 0 ||
				strcmp(input, "falsehope") == 0)
				return SELECT_FOUR;

			if (strcmp(input, "five") == 0 ||
				strcmp(input, "5") == 0 ||
				strcmp(input, "twinpeak") == 0)
				return SELECT_FIVE;
		}

		// Primes the fast forward command
		if (strcmp(input, "goto") == 0)
		{
			bFastForward = true;
		}

		// Primes the select command
		if (strcmp(input, "select") == 0)
		{
			bSelect = true;
		}

		char next = cin.peek();
		if (next == '\n' || next == EOF)
			break;
		for (int i = 0; i < 50; i++)
		{
			input[i] = '\0';
		}
		cin >> input;
	}

	return INVALID;
}

void Game::CommenceEndGame()
{

}

void Game::FormInt(short pTargetDay[3])
{
	/*pTargetDay stores the number in an array in reverse to account for
	variance in the digits of the number. (274 -> 4 7 2)*/

	m_targetDay = pTargetDay[0] + (10 * pTargetDay[1]) + (100 * pTargetDay[2]);

	// Clamps the target day between 0 and 365 inclusive
	if (m_targetDay > 365)
		m_targetDay = 365;
	else if (m_targetDay < 0)
		m_targetDay = 0;
}

char Game::GetDataFromArray(byte pHorizontal, byte pVertical)
{
	// The lines are drawn between the values

	// 0-m_maxValue value is scaled to 0-DETAIL
	unsigned int leftValue = DETAIL - (m_dataRef[pHorizontal] / (m_maxValue / DETAIL));
	unsigned int rightValue = DETAIL - (m_dataRef[pHorizontal + 1] / (m_maxValue / DETAIL));
	
	if (leftValue == 0 && rightValue == 0)
		return ' ';
	else if (leftValue == rightValue && leftValue == pVertical)
		return '_';
	else if (leftValue < rightValue && leftValue == pVertical)
		return '\\';
	else if (leftValue > rightValue && rightValue == pVertical)
		return '/';
	else
		// If there was some kind of error
		return ' ';
}

void Game::UpdateMaxValue()
{
	// Loop through all companies checking if max value has been exceeded
	// if it has, double it and recheck all companies
	bool exceeded;
	do
	{
		exceeded = false;
		for (int i = 0; i < COMPAMOUNT; i++)
		{
			if (m_companies[i].GetCurrentValue() > m_maxValue)
			{
				m_maxValue = m_maxValue << 1;
				exceeded = true;
				break;
			}
		}
	} while (exceeded);
}

void Game::UpdateMoneyText()
{
	m_moneyText = "$" + m_money;
}

void Game::DrawHeader()
{
	cout << "\t      Stock Trader\n"
		<< " A simple game of buying and selling shares.\n"
		<< "  Your goal is to buy and sell shares to\n"
		<< "   make as much profit as you can in one\n"
		<< "       year(365 days). Good luck!\n" << endl;
}

void Game::DrawGraph()
{
	// Obtains a local reference to the selected companies graph data
	m_dataRef = m_companies[m_currentlySelected].GetCompanyData();

	// Prints currently selected company name
	cout << " " << m_companies[m_currentlySelected].GetName() << endl;

	// Top edge of graph box
	cout << TOP_LEFT;
	for (int i = 0; i < WIDTH - 2; i++)
	{
		cout << HORIZONTAL;
	}
	cout << TOP_RIGHT;

	// Two for loops that print out the graph into the edge box
	for (int y = 0; y < DETAIL; y++)
	{
		cout << VERTICAL;
		for (int x = 0; x < WIDTH - 2; x++)
		{
			cout << GetDataFromArray(x, y);
		}
		cout << VERTICAL;
	}

	// Bottom edge of graph box
	cout << BOTTOM_LEFT;
	for (int i = 0; i < WIDTH - 2; i++)
	{
		cout << HORIZONTAL;
	}
	cout << BOTTOM_RIGHT << endl;
}

void Game::DrawInfo()
{
	cout << "\n Day: " << m_currentDay << endl;
	cout << " Money: " << m_moneyText << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << " Company: " << m_companies[i].GetName() << ": "
			<< m_companies[i].GetCurrentValue() << endl;
	}
	cout << endl;
	for (int i = 0; i < WIDTH; i++)
	{
		cout << FLAT_LINE;
	}
	cout << endl;

	cout << " Bitdata: " << (int)m_bitData << endl;

	if (m_currentDay == 0 && GetZeroMessage())
		cout << " Type 'help' for commands" << endl;

	if (GetInvalid())
		cout << " Invalid input - Type 'help' for accepted commands" << endl;

	if (GetHelp())
	{
		cout << " Commands are:\n"
			<< " 'help'                   | Lists these commands\n"
			<< " 'end day', 'next' or 'n' | Ends current day and moves on to the next\n"
			<< " 'goto <day>'             | Skips ahead to specified day\n"
			<< " 'buy'                    | Does nothing currently\n"
			<< " 'sell'                   | Does nothing currently\n"
			<< " 'select <company name>'  | Chooses the current company to be displayed\n\n"
			<< " NOTE: All commands are lower case." << endl;
	}
}

void Game::ClearBitData()
{
	m_bitData = 0;
}

void Game::SetGameOver(bool pState)
{
	m_bitData = pState ? m_bitData | 1 : m_bitData & 254;
}

void Game::SetZeroMessage(bool pState)
{
	m_bitData = pState ? m_bitData | 2 : m_bitData & 253;
}

void Game::SetEndDay(bool pState)
{
	m_bitData = pState ? m_bitData | 4 : m_bitData & 251;
}

void Game::SetHelp(bool pState)
{
	m_bitData = pState ? m_bitData | 8 : m_bitData & 247;
}

void Game::SetInvalid(bool pState)
{
	m_bitData = pState ? m_bitData | 16 : m_bitData & 239;
}

bool Game::GetGameOver() const
{
	if ((1 & m_bitData) == 1)
		return true;
	else
		return false;
}

bool Game::GetZeroMessage() const
{
	if ((2 & m_bitData) == 2)
		return true;
	else
		return false;
}

bool Game::GetEndDay() const
{
	if ((4 & m_bitData) == 4)
		return true;
	else
		return false;
}

bool Game::GetHelp() const
{
	if ((8 & m_bitData) == 8)
		return true;
	else
		return false;
}

bool Game::GetInvalid() const
{
	if ((16 & m_bitData) == 16)
		return true;
	else
		return false;
}
