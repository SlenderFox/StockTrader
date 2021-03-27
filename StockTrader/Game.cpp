#include "Game.h"
#include <Windows.h>
#include <random>
#include <time.h>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

void Game::Run()
{
	if (!Startup())
		return;

	while (true)
	{
		Update();
	}
}

bool Game::Startup()
{
	srand((unsigned int)time(nullptr));
	HWND hwnd = GetConsoleWindow();
	// Rect is ordered left, top, right, bottom
	RECT rect = { 50, 50, (WIDTH * CHARWIDTH + 33), 900};
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

bool Game::Update()
{
	StepDay();
	UpdateMaxValue();
	UpdateMoneyText();

	// Ends game when year ends
	if (m_day == 366)
	{
		SetGameOver();
		// Currently the program just ends
		return false;
	}

	// Clears the console
	system("cls");
	// Draw the graph of the currently selected company
	DrawGraph();
	// Draw current game info
	DrawInfo();
	// Draw the in-game console
	DrawConsole();

	// Asks the user for input
	UserInput();

	return true;
}

void Game::UserInput()
{
	ResetState();

	// Ready for player input
	bool bSelect = false;
	bool bFastForward = false;
	bool bBuy = false;
	bool bSell = false;
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

		// After invoking the fast forward command, process input as number
		if (bFastForward)
		{
			try
			{
				string num = input;
				unsigned int val = std::stoi(num);
				if (val < 0)
					val = 0;
				else if (val > 365)
					val = 365;
				m_targetDay = val;
				GotoDay(m_targetDay);
				return;
			}
			catch (const std::exception&)
			{
				break;
			}
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
				m_selected = val - 1;
				return;
			}
			catch (const std::exception&)
			{
				break;
			}
		}

		// After invoking the buy command, process input as number
		if (bBuy)
		{
			try
			{
				string num = input;
				unsigned int val = std::stoi(num);
				if (val < 0)
					val = 0;
				else if (val > MAXTRANSFER)
					val = MAXTRANSFER;
				BuySellFromCompany(val);
				return;
			}
			catch (const std::exception&)
			{
				break;
			}
		}

		// After invoking the sell command, process input as number
		if (bSell)
		{
			try
			{
				string num = input;
				int val = std::stoi(num);
				if (val < 0)
					val = 0;
				else if (val > MAXTRANSFER)
					val = MAXTRANSFER;
				BuySellFromCompany(-val);
				return;
			}
			catch (const std::exception&)
			{
				break;
			}
		}

		// Primes the fast forward command
		if (strcmp(input, "goto") == 0) { bFastForward = true; }
		// Primes the select command
		if (strcmp(input, "select") == 0) { bSelect = true; }
		// Primes the buy command
		if (strcmp(input, "buy") == 0) { bBuy = true; }
		// Primes the sell command
		if (strcmp(input, "sell") == 0) { bSell = true; }

		char next = cin.peek();
		if (next == '\n' || next == EOF)
			break;
		for (int i = 0; i < 50; i++)
		{
			input[i] = '\0';
		}
		cin >> input;
	}

	// Failed input handling
	if (bFastForward) { SetInvalid("Invalid value entered"); }
	else if (bSelect) { SetInvalid("Invalid value entered"); }
	else if (bBuy) { SetInvalid("Invalid value entered"); }
	else if (bSell) { SetInvalid("Invalid value entered"); }
	else { SetInvalid("Command not found"); }
	return;
}

bool Game::InitialiseCompanies()
{
	// Creates 5 new empty companies
	m_companies = new Company[NUMCOMPANIES];

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
	m_selected = 0;

	return true;
}

void Game::StepDay()
{
	// Makes sure that the user wants the day to end
	if (GetEndDay())
	{
		m_day++;
		for (int i = 0; i < 5; i++)
		{
			// Updates the data array for each company
			m_companies[i].UpdateCompanyValue(-0.05f, 0.08f);
		}
		ResetState();
	}
}

void Game::GotoDay(short pTargetDay)
{
	if (pTargetDay <= m_day)
		return;

	// Continually steps through the days until the target day is reached
	while (m_day < pTargetDay)
	{
		SetEndDay();
		StepDay();
	}
}

void Game::CommenceEndGame()
{

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
	byte sets = m_money / 3;
	byte remainder = m_money % 3;
	m_moneyText = std::to_string(m_money);
	m_moneyText = "$" + m_moneyText;
}

void Game::BuySellFromCompany(int pAmount)
{
	// pAmount will be positive to buy and negative to sell
	if ((int)m_companies[m_selected].GetOwnedStocks() + pAmount >= 0)
	{
		int cost = pAmount * m_companies[m_selected].GetCurrentValue();
		if (m_money - cost >= 0)
		{
			m_money -= cost;
			m_companies[m_selected].ModifyOwnedStocks(pAmount);
		}
		else
		{
			SetInvalid("You don't have enough money");
		}
	}
	else
	{
		SetInvalid("You can't sell more stocks than you currently own");
	}
}

void Game::DrawGraph()
{
	// Obtains a local reference to the selected companies graph data
	m_dataRef = m_companies[m_selected].GetCompanyData();

	// Prints currently selected company name
	cout << " " << m_companies[m_selected].GetName() << endl;

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
	cout << " Day: " << m_day << endl;
	cout << " Money: " << m_moneyText << endl;

	for (int i = 0; i < NUMCOMPANIES; i++)
	{
		cout << " " << m_companies[i].GetName() << ": "
			<< m_companies[i].GetCurrentValue() << ", "
			<< m_companies[i].GetOwnedStocks() << endl;
	}

	cout << " Max value: " << m_maxValue << endl;
	
	//cout << endl;
	for (int i = 0; i < WIDTH; i++)
	{
		cout << FLAT_LINE;
	}
	cout << endl;
}

void Game::DrawConsole()
{
	if (GetInvalid())
		cout << m_invalidMessage << " - Type 'help' for a list of accepted commands" << endl;

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
			<< " 'goto <day>'         | Skips ahead to specified day\n"
			<< " 'select <input>'     | Chooses the current company to be displayed\n"
			<< " 'buy <input>'        | Attempts to buy stocks of the selected company\n"
			<< " 'sell <input>'       | Attempts to sell stocks of the selected company\n\n"
			<< " NOTE: All commands are lower case." << endl;
	}
}

void Game::SetInvalid(string pMessage)
{
	m_state = State::Invalid;
	m_invalidMessage = " " + pMessage;
}
