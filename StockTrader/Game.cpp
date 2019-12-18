/*------------------------------------------------------
	File Name: Game.cpp
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)
------------------------------------------------------*/

#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <random>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

Game::Game() : m_endDay(false), m_gameOver(false)
{
	m_companies = new Companies[5];
}

Game::~Game()
{
	delete[] m_companies;
}

bool Game::Startup()
{
	srand(time(nullptr));
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 0, 0 , 675, 900};
	MoveWindow(hwnd, rect.top, rect.left, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	if (!InitialiseCompanies())
		return false;

	return true;
}

bool Game::InitialiseCompanies()
{
	//Creates 5 companies stored on the heap
	m_companies = new Companies[5];

	// Initialises each company
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			m_companies[i].InitializeCompany(i, "Flat");
			break;
		case 1:
			m_companies[i].InitializeCompany(i, "Growth");
			break;
		case 2:
			m_companies[i].InitializeCompany(i, "UpNDown");
			break;
		case 3:
			m_companies[i].InitializeCompany(i, "FalseHope");
			break;
		case 4:
			m_companies[i].InitializeCompany(i, "TwinPeaks");
			break;
		}
	}

	// Sets default selected company
	m_player.m_currentlySelected = 0;

	return true;
}

void Game::ImportGraph(char compGraphArr[20][78])
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 78; x++)
		{
			m_graphArray[y][x] = compGraphArr[y][x];
		}
	}
}

void Game::GotoDay(int pTargetDay)
{
	if (pTargetDay <= m_day) return;

	while (m_day < pTargetDay)
	{
		m_endDay = true;
		StepDay();
	}
}

void Game::StepDay()
{
	// Makes sure that the user wants the day to end
	if (m_endDay)
	{
		// For ever day except the first one update the company value
		if (m_day != 1)
		{
			for (int i = 0; i < 5; i++)
			{
				m_companies[i].UpdateValue();
			}
		}

		// Updates the graph for each company
		for (int i = 0; i < 5; i++)
		{
			m_companies[i].UpdateCompGraph();
		}

		m_day++;
		m_endDay = false;
	}
}

void Game::FormInt()
{
	/*The int array arrTargetDay stores the number that will be converted to an
	interger in reverse within the array (274 -> 4 7 2) because the length of
	the number can be between 1 and 3 digits. This means that the number will
	always have a ones digit, so making it the first value was the easiest way.*/

	int hundreds = 0;
	int tens = 0;
	int ones = 0;

	ones = m_arrTargetDay[0];

	if (m_targetDayLength > 1)
	{
		tens = m_arrTargetDay[1];
		tens *= 10;

		if (m_targetDayLength > 2)
		{
			hundreds = m_arrTargetDay[2];
			hundreds *= 100;
		}
	}

	m_targetDay = hundreds + tens + ones;

	if (m_targetDay > 365)
		m_targetDay = 365;
}

void Game::Update()
{
	// Ends game when year ends
	if (m_day == 365)
	{
		m_gameOver = true;
		return;
	}

	StepDay();
	m_player.UpdateMoneyName();
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
	int command = GetCommand();

	switch (m_player.ExecuteCommand(command))
	{
	case 1:
		m_endDay = true;
		break;
	case 2:
		FormInt();
		GotoDay(m_targetDay);
		break;
	default:
		break;
	}
}

bool Game::IsGameOver()
{
	return m_gameOver;
}

void Game::DrawHeader()
{
	cout << INDENT << INDENT << INDENT << INDENT << "Stock Trader" << endl;
	cout << INDENT << "A simple game of trading shares. Your goal is to buy and sell" << endl;
	cout << INDENT << "shares to make as much profit as you can in one year (365 days)," << endl;
	cout << INDENT << "you make these trades using gold coins (gold). Good luck!" << endl;
	cout << INDENT << INDENT << INDENT << "(Type 'help' for help)" << endl << endl;
}

void Game::DrawGraph()
{
	// Prints currently selected company name
	cout << m_companies[m_player.m_currentlySelected].GetName() << endl;

	// Top edge of graph box
	cout << TOP_LEFT;
	for (int i = 0; i < 78; i++)
	{
		cout << HORIZONTAL;
	}
	cout << TOP_RIGHT;

	// Loads graph of currently selected company
	ImportGraph(m_companies[m_player.m_currentlySelected].m_companyArray);

	// Two for loops that print out the graph into the edge box
	for (int y = 0; y < 20; y++)
	{
		cout << VERTICAL;
		for (int x = 0; x < 78; x++)
		{
			cout << m_graphArray[y][x];
		}
		cout << VERTICAL;
	}

	// Bottom edge of graph box
	cout << BOTTOM_LEFT;
	for (int i = 0; i < 78; i++)
	{
		cout << HORIZONTAL;
	}
	cout << BOTTOM_RIGHT << endl;
}

void Game::DrawInfo()
{
	cout << "Day: " << m_day << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << endl << "Company: " << m_companies[i].GetName() << " "
			<< m_companies[i].GetCurrentValue();
	}

	cout << endl << "Money: " << /*m_player.moneyName*/ m_player.m_money << endl;

	cout << endl << endl;
	for (int i = 0; i < 80; i++)
	{
		cout << HORIZONTAL;
	}
	cout << endl;
}

int Game::GetCommand()
{
	// Ready for player input
	char input[50] = "\0";
	cout << ">";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> input;

	bool bSelect = false;
	bool bEndDay = false;
	bool bFastForward = false;
	// Input loop
	while (input)
	{
		// Select current company to display
		if (strcmp(input, "select") == 0)
		{
			bSelect = true;
		}
		else if (bSelect)
		{
			if (strcmp(input, "flat") == 0)
				return FLAT;

			if (strcmp(input, "growth") == 0)
				return GROWTH;

			if (strcmp(input, "upndown") == 0)
				return UPNDOWN;

			if (strcmp(input, "falsehope") == 0)
				return FALSEHOPE;

			if (strcmp(input, "twinpeaks") == 0)
				return TWINPEAKS;
		}

		// End current day and move to the next
		if (strcmp(input, "end") == 0)
		{
			bEndDay = true;
		}
		else if (bEndDay)
		{
			if (strcmp(input, "day") == 0)
				return ENDDAY;
		}

		if (strcmp(input, "n") == 0)
			return ENDDAY;

		// Display all commands
		if (strcmp(input, "help") == 0)
			return HELP;

		// Fast forwards through days until entered day
		if (strcmp(input, "goto") == 0)
		{
			bFastForward = true;
		}
		else if (bFastForward)
		{
			if (input[1] != '\0')
			{
				if (input[2] != '\0')
				{
					// Means number is triple digit
					m_arrTargetDay[0] = input[2];	//Ones
					m_arrTargetDay[1] = input[1];	//Tens
					m_arrTargetDay[2] = input[0];	//Hundreds

					m_arrTargetDay[0] -= 48;
					m_arrTargetDay[1] -= 48;
					m_arrTargetDay[2] -= 48;

					m_targetDayLength = 3;
				}
				else
				{
					// Means nunber is double digit
					m_arrTargetDay[0] = input[1];	//Ones
					m_arrTargetDay[1] = input[0];	//Tens

					m_arrTargetDay[0] -= 48;
					m_arrTargetDay[1] -= 48;

					m_targetDayLength = 2;
				}
			}
			else
			{
				// Means number is single digit
				m_arrTargetDay[0] = input[0];		//Ones
				m_arrTargetDay[0] -= 48;
			}

			return FASTFORWARD;
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
	
	return 0;
}
