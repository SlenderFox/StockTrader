/*------------------------------------------------------
	File Name: Game.h
	Author: Dylan Glenister
	Modified: 20/12/19 (dd/mm/yy)

	Where all the main game logic is stored and executed
------------------------------------------------------*/

#pragma once
#include "Companies.h"
#include "Player.h"

class Game
{
	// Functions
public:
	Game() : m_player(nullptr), m_companies(nullptr), m_dataRef(nullptr) {}
	~Game()
	{
		delete m_player;
		delete[] m_companies;
		delete[] m_dataRef;
	}

	bool Startup();		//General initialisation
	void Update();			//Called to update though game functions
	void Draw();			//Prints out to console
	void UserInput();		//Asks user for input then handles it

	bool GetGameOver();	//Returns gameover state

private:
	bool InitialiseCompanies();					//Creation and initialisation of companies
	bool InitialisePlayer();						//Creation and initialisation of player
	void StepDay();								//Moves ahead exactly one day
	void GotoDay(short);						//Function used to skip ahead in days
	void FormInt(short[3]);						//Turns an char array into a single interger
	char GetDataFromArray(byte, byte);	//Returns the character corresponding to the data array
	byte GetCommand();							//Function to handle user input

	void DrawHeader();		//Prints out title and description
	void DrawGraph();		//Prints the graph of the current company
	void DrawInfo();			//Prints info about companies and player

	void SetGameOver(bool);	//Set gameover state
	void SetEndDay(bool);		//Set endday state
	void SetHelp(bool);			//Set help state
	void SetInvalid(bool);		//Set invalid state

	bool GetEndDay();		//Returns endday state
	bool GetHelp();			//Returns help state
	bool GetInvalid();			//Returns invalid state

	// Variables
private:
	byte m_bitData = 0;								//gameOver-EndDay-Help-Invalid
	byte m_currentlySelected = 0;				//The company currently selected for display
	short m_currentDay = 0;						//Current day
	short m_targetDay = 0;							//Used when fast forwarding

	Player *m_player;					//Reference to the player
	Companies *m_companies;		//For creating companies on the heap
	unsigned short *m_dataRef;	//A local reference for the currently selected company data
};
