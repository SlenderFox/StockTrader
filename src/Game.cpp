#include "Game.hpp"
#include <random>
#include <time.h>
#include <sstream>
#include <iostream>
#include "windumb.hpp"
#include "Renderer.hpp"

using std::cout;
using std::cin;
using std::string;
using std::to_string;

Game::~Game()
{ delete[] m_companies; }

void Game::Run()
{
	if (!Startup())
		return;

	// This loop allows for the game to be played multiple times
	while (!m_closeApp)
	{
		while (Update()) {}

		if (!Renderer::EndGame(m_companies, m_money))
			ResetGame();
		else
			m_closeApp = true;
	}
}

bool Game::Startup() noexcept
{
	// TODO: Don't use
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
			m_companies[i].InitialiseCompany(Company::Type::Flat, "Flat", 100);
			break;
		case 1:
			m_companies[i].InitialiseCompany(Company::Type::Growth, "Growth", 100);
			break;
		case 2:
			m_companies[i].InitialiseCompany(Company::Type::UpNDown, "UpNDown", 100);
			break;
		case 3:
			m_companies[i].InitialiseCompany(Company::Type::FalseHope, "FalseHope", 100);
			break;
		case 4:
			m_companies[i].InitialiseCompany(Company::Type::TwinPeaks, "TwinPeaks", 100);
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

	// TODO: Look into
	// Clears the console
	system("cls");
	// Draw the graph of the currently selected company
	Renderer::DrawGraph(m_companies, m_selected, m_maxValue);
	// Draw current game info
	Renderer::DrawInfo(m_companies, m_day, m_money);
	// Draw the in-game console
	Renderer::DrawConsole(m_state, m_invalidMessage);
	cout.flush();

	// Asks the user for input
	if (m_state != State::Goto)
		UserInput();

	return true;
}

bool Game::StepDay() noexcept
{
	// Makes sure that the user wants the day to end
	if (m_state == State::EndDay || m_state == State::Goto)
	{
		m_day++;
		// Ends game when year ends
		if (m_day == 366)
		{
			m_state = State::GameOver;
			// Currently the program just ends
			return false;
		}
		for (uint8 i = 0; i < NUMCOMPANIES; i++)
		{
			// Updates the data array for each company
			m_companies[i].UpdateCompanyValue(-0.05f, 0.06f);
			if (m_companies[i].GetCurrentValue() > m_maxValue)
				m_maxValue <<= 1;
		}

		// If goto has been called and target day has not been reached, prevent state from being reset
		if (m_state == State::Goto && m_day != m_targetDay)
			return true;

		m_state = State::Clear;
	}
	return true;
}

void Game::UserInput()
{
	m_state = State::Clear;

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
			m_state = State::Help;
			return;
		}

		// End current day and move to the next
		if (strcmp(input, "end") == 0 ||
			strcmp(input, "next") == 0 ||
			strcmp(input, "n") == 0)
		{
			m_state = State::EndDay;
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
			catch (const std::exception &e) { throw e; }
			break;
		case State::Select:
			// After invoking the select command, searches for a valid request
			try
			{
				string num = input;
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
			catch (const std::exception &e) { throw e; }
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
			catch (const std::exception &e) { throw e; }
			break;
		default:
			break;
		}

		// Primes the fast forward command
		if (strcmp(input, "goto") == 0) { m_state = State::Goto; }
		// Primes the select command
		if (strcmp(input, "select") == 0) { m_state = State::Select; }
		// Primes the buy command
		if (strcmp(input, "buy") == 0) { m_state = State::Buy; }
		// Primes the sell command
		if (strcmp(input, "sell") == 0) { m_state = State::Sell; }

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
	if (m_state == State::Goto) { SetInvalid("Invalid value entered, please enter a number between today and 365"); }
	else if (m_state == State::Select) { SetInvalid("Invalid value entered"); }
	else if (m_state == State::Buy) { SetInvalid("Invalid value entered"); }
	else if (m_state == State::Sell) { SetInvalid("Invalid value entered"); }
	else { SetInvalid("Command not found"); }
	cout.flush();
	return;
}

void Game::ResetGame() noexcept
{
	m_state = State::Info;
	m_day = 0;
	m_targetDay = 0;
	m_maxValue = 512;
	m_money = STARTINGCASH;

	InitialiseCompanies();	// Sets m_selected to 0
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
