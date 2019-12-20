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
	if (!InitialisePlayer() || !InitialiseCompanies())
		return false;

	return true;
}

void Game::Update()
{
	// Ends game when year ends
	if (m_currentDay == 365)
	{
		SetGameOver(true);
		return;
	}

	StepDay();
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
	switch (GetCommand())
	{
	case 0:	//HELP
		SetHelp(true);
		break;
	case 1:	//ENDDAY
		SetEndDay(true);
		break;
	case 2:	//FASTFORWARD
		GotoDay(m_targetDay);
		break;
	case 3:	//BUY
		break;
	case 4:	//SELL
		break;
	case 5:	//SELECT_ONE
		m_currentlySelected = 0;
		break;
	case 6:	//SELECT_TWO
		m_currentlySelected = 1;
		break;
	case 7:	//SELECT_THREE
		m_currentlySelected = 2;
		break;
	case 8:	//SELECT_FOUR
		m_currentlySelected = 3;
		break;
	case 9:	//SELECT_FIVE
		m_currentlySelected = 4;
		break;
	case 10:	//INVALID
	default:	//INVALID
		SetInvalid(true);
		break;
	}
}

bool Game::InitialiseCompanies()
{
	// Creates 5 new empty companies
	m_companies = new Companies[5];

	// Initialises each company
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
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

bool Game::InitialisePlayer()
{
	m_player = new Player();
	return true;
}

void Game::StepDay()
{
	// Makes sure that the user wants the day to end
	if (GetEndDay())
	{
		for (int i = 0; i < 5; i++)
		{
			m_companies[i].UpdateValue(-5, 20);
			// Updates the data array for each company
			m_companies[i].UpdateCompanyData();
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

void Game::FormInt(short pIntArray[3])
{
	/*The int array arrTargetDay stores the number that will be converted to an
	interger in reverse within the array (274 -> 4 7 2) because the length of
	the number can be between 1 and 3 digits. This means that the number will
	always have a ones digit, so making it the first value was the easiest way.*/

	m_targetDay = pIntArray[0] + (10 * pIntArray[1]) + (100 * pIntArray[3]);

	//ones = m_arrTargetDay[0];

	//if (m_targetDayLength > 1)
	//{
	//	tens = m_arrTargetDay[1];
	//	tens *= 10;

	//	if (m_targetDayLength > 2)
	//	{
	//		hundreds = m_arrTargetDay[2];
	//		hundreds *= 100;
	//	}
	//}

	//m_targetDay = hundreds + tens + ones;

	if (m_targetDay > 365)
		m_targetDay = 365;
}

char Game::GetDataFromArray(byte pHorizontal, byte pVertical)
{
	m_dataRef = m_companies[m_currentlySelected].GetCompanyData();
	unsigned short currentValue = DETAIL - (m_dataRef[pHorizontal] / (1000 / DETAIL));
	unsigned short previousValue = DETAIL - (m_dataRef[pHorizontal + 1] / (1000 / DETAIL));

	// Converts the 0-1000 value into 0-DETAIL
	if (currentValue != pVertical)
		return ' ';

	if (currentValue == previousValue)
	{
		return '_';
	}
	else if (currentValue < previousValue)
	{
		return '\\';
	}
	else if (currentValue > previousValue)
	{
		return '/';
	}

	// If there was some kind of error
	return '=';
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

		// After invoking the select command, searches for a valid request
		if (bSelect)
		{
			if (strcmp(input, "flat") == 0 ||
				strcmp(input, "1") == 0 ||
				strcmp(input, "one") == 0)
				return SELECT_ONE;

			if (strcmp(input, "growth") == 0 ||
				strcmp(input, "2") == 0 ||
				strcmp(input, "two") == 0)
				return SELECT_TWO;

			if (strcmp(input, "upndown") == 0 ||
				strcmp(input, "3") == 0 ||
				strcmp(input, "three") == 0)
				return SELECT_THREE;

			if (strcmp(input, "falsehope") == 0 ||
				strcmp(input, "4") == 0 ||
				strcmp(input, "four") == 0)
				return SELECT_FOUR;

			if (strcmp(input, "twinpeak") == 0 ||
				strcmp(input, "5") == 0 ||
				strcmp(input, "five") == 0)
				return SELECT_FIVE;
		}

		// After invoking the fast forward command, process as number
		if (bFastForward)
		{
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
	// Prints currently selected company name
	cout << m_companies[m_currentlySelected].GetName() << endl;

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
	cout << "\nDay: " << m_currentDay << endl;
	cout << "Money: " << /*m_player.moneyName*/ m_player->GetMoney() << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "Company: " << m_companies[i].GetName() << ": "
			<< m_companies[i].GetCurrentValue() << endl;
	}
	cout << endl;
	for (int i = 0; i < WIDTH; i++)
	{
		cout << FLAT_LINE;
	}
	cout << endl;

	if (m_currentDay == 1)
		cout << "Type 'help' for commands" << endl;

	if (GetInvalid())
		cout << "Invalid input - Type 'help' for accepted commands";

	if (GetHelp())
	{
		cout << "\nCommands are:\n"
			<< "'help'                   | Lists these commands\n"
			<< "'end day', 'next' or 'n' | Ends current day and moves on to the next\n"
			<< "'goto <day>'             | Skips ahead to specified day\n"
			<< "'buy'                    | Does nothing currently\n"
			<< "'sell'                   | Does nothing currently\n"
			<< "'select <company name>'  | Chooses the current company to be displayed\n\n"
			<< "NOTE: All commands are lower case.\n" << endl;
	}
}

void Game::SetGameOver(bool)
{
	m_bitData = m_bitData | 1;
}

void Game::SetEndDay(bool)
{
	m_bitData = m_bitData | 2;
}

void Game::SetHelp(bool)
{
	m_bitData = m_bitData | 4;
}

void Game::SetInvalid(bool)
{
	m_bitData = m_bitData | 8;
}

bool Game::GetGameOver()
{
	if ((1 & m_bitData) == 1)
		return true;
	else
		return false;
}

bool Game::GetEndDay()
{
	if ((2 & m_bitData) == 2)
		return true;
	else
		return false;
}

bool Game::GetHelp()
{
	if ((4 & m_bitData) == 4)
		return true;
	else
		return false;
}

bool Game::GetInvalid()
{
	if ((8 & m_bitData) == 8)
		return true;
	else
		return false;
}
