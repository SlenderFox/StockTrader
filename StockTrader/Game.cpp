/*------------------------------------------------------
	Filename: Game.cpp
	Author: Dylan Glenister
	Modified: 25/02/21 (dd/mm/yy)
------------------------------------------------------*/

#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <random>
#include <time.h>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

bool Game::Startup()
{
	srand((unsigned int)time(nullptr));
	HWND hwnd = GetConsoleWindow();
	// Rect is ordered left, top, right, bottom
	RECT rect = { 50, 50, (WIDTH * 8 + 33), 900};
	if (!MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, TRUE))
		return false;
	// I have no idea what these numbers mean but I dont want to remove them
	// 80-673
	// 100-833

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
		{
			SetHelp(true);
			return;
		}

		// End current day and move to the next
		if (strcmp(input, "end") == 0 ||
			strcmp(input, "next") == 0 ||
			strcmp(input, "n") == 0)
		{
			SetEndDay(true);
			return;
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
			GotoDay(m_targetDay);
			return;
		}

		// After invoking the select command, searches for a valid request
		if (bSelect)
		{
			try
			{
				string num = input;
				unsigned int val = std::stoi(num);
				if (val < 1)
					val = 1;
				else if (val > NUMCOMPANIES)
					val = NUMCOMPANIES;
				m_currentlySelected = val - 1;
			}
			catch (const std::exception&)
			{
				m_currentlySelected = 0;
			}
			return;
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

	SetInvalid(true);
	return;
}

bool Game::InitialiseCompanies()
{
	// Creates 5 new empty companies
	m_companies = new Company[NUMCOMPANIES];

	// Feels kind of pointless doing this in a for loop
	// Initialises each company
	for (int i = 0; i < NUMCOMPANIES; i++)
	{
		// Temp for testing
		switch (i)
		{
		default:
		case 0:
			m_companies[i].InitialiseCompany(CompanyType::FLAT, "Flat", 100);
			break;
		case 1:
			m_companies[i].InitialiseCompany(CompanyType::GROWTH, "Growth", 100);
			break;
		case 2:
			m_companies[i].InitialiseCompany(CompanyType::UPNDOWN, "UpNDown", 100);
			break;
		case 3:
			m_companies[i].InitialiseCompany(CompanyType::FALSEHOPE, "FalseHope", 100);
			break;
		case 4:
			m_companies[i].InitialiseCompany(CompanyType::TWINPEAKS, "TwinPeaks", 100);
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
		m_currentDay++;
		for (int i = 0; i < 5; i++)
		{
			// Updates the data array for each company
			m_companies[i].UpdateCompanyValue(-0.05f, 0.1f);
		}
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
	// (Should be from 0 to DETAIL-1 but done this way to prevent clipping)
	// Inverts vertical from DETAIL-1 to 0 to 0 to DETAIL
	pVertical = DETAIL - pVertical;
	// 0 to m_maxValue value is scaled to 0 to DETAIL
	unsigned int leftValue = (int)(m_dataRef[WIDTH - 2 - pHorizontal] / (float)(m_maxValue / DETAIL));
	unsigned int rightValue = (int)(m_dataRef[WIDTH - 3 - pHorizontal] / (float)(m_maxValue / DETAIL));
	
	if (m_dataRef[WIDTH - 2 - pHorizontal] == NULL)
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

void Game::UpdateMaxValue()
{
	// Loop through all companies checking if max value has been exceeded
	// if it has, double it and recheck all companies
	bool exceeded = false;
	do
	{
		exceeded = false;
		for (int i = 0; i < NUMCOMPANIES; i++)
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
		<< "       year (365 days). Good luck!\n" << endl;
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
	cout << " Day: " << m_currentDay << endl;
	cout << " Money: " << m_moneyText << endl;

	for (int i = 0; i < NUMCOMPANIES; i++)
	{
		cout << " Company: " << m_companies[i].GetName() << ": "
			<< m_companies[i].GetCurrentValue() << endl;
	}

	cout << " Max value: " << m_maxValue << endl;
	
	cout << " Bitdata: ";
	if (m_bitData & 128) cout << "1"; else cout << "0";
	if (m_bitData & 64) cout << "1"; else cout << "0";
	if (m_bitData & 32) cout << "1"; else cout << "0";
	if (m_bitData & 16) cout << "1"; else cout << "0";
	if (m_bitData & 8) cout << "1"; else cout << "0";
	if (m_bitData & 4) cout << "1"; else cout << "0";
	if (m_bitData & 2) cout << "1"; else cout << "0";
	if (m_bitData & 1) cout << "1"; else cout << "0";
	cout << " (" << (int)m_bitData << ")" << endl;

	cout << endl;
	for (int i = 0; i < WIDTH; i++)
	{
		cout << FLAT_LINE;
	}
	cout << endl;

	if (m_currentDay == 0 && GetZeroMessage())
		cout << " Type 'help' for commands" << endl;

	if (GetInvalid())
		cout << " Invalid input - Type 'help' for accepted commands" << endl;

	if (GetHelp())
	{
		cout << " Commands are:\n"
			<< " 'help'               | Lists these commands\n"
			<< " 'end day'/'next'/'n' | Ends current day and moves on to the next\n"
			<< " 'goto <day>'         | Skips ahead to specified day\n"
			<< " 'select <input>'     | Chooses the current company to be displayed\n"
			<< " 'buy <input>'        | Attempts to buy stocks of the selected company\n"
			<< " 'sell <input>'       | Attempts to sell stocks of the selected company\n\n"
			<< " NOTE: All commands are lower case." << endl;
	}
}

void Game::ClearBitData()
{
	m_bitData &= 1;
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
