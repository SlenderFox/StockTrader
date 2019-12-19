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
	Game();
	~Game();

	bool Startup();		//General initialisation
	void Update();			//Called to update though game functions
	void Draw();			//Prints out to console
	void UserInput();		//Asks user for input then handles it

private:
	bool InitialiseCompanies();		//Creation and initialisation of companies
	void LoadCompanyData();		//Copies company graph into printable graph
	void GotoDay(short);			//Function used to skip ahead in days
	void StepDay();					//Moves ahead exactly one day
	void FormInt();					//Turns an interger array into a single interger (used to convert from char array to int)

	void DrawHeader();	//Prints out title and description
	void DrawGraph();	//Prints the graph of the current company
	void DrawInfo();		//Prints info about companies and player

	int GetCommand();	//Function to handle user input

	// Variables
public:
	bool m_gameOver;	//Whether the program wants to end itself

private:
	bool m_endDay;						//Whether the program wants to end the day or not
	byte m_day = 0;							//Current day
	byte m_arrTargetDay[3];			//String of numbers converted into an int array
	byte m_targetDayLength = 1;		//Used to assist when converting from char to int
	byte m_targetDay;						//Used when fast forwarding

	byte m_currentGraph[20][78];	//The printable graph
	Companies *m_companies;			//For creating companies on the heap
	Player *m_player;						//Reference to the player
};
