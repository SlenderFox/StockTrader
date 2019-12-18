/*------------------------------------------------------
	File Name: Game.h
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)
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
	bool IsGameOver();	//Returns true/false based on if game is over

private:
	bool InitialiseCompanies();								//Creation and initialisation of companies
	void ImportGraph(char compGraphArr[20][78]);	//Copies company graph into printable graph
	void GotoDay(int pTargetDay);						//Function used to skip ahead in days
	void StepDay();											//Moves ahead exactly one day
	void FormInt();											//Turns an interger array into a single interger (used to convert from char array to int)

	void DrawHeader();	//Prints out title and description
	void DrawGraph();	//Prints the graph of the current company
	void DrawInfo();		//Prints info about companies and player

	int GetCommand();	//Function to handle user input

	// Variables
private:
	bool m_endDay;					//Whether the program wants to end the day or not
	bool m_gameOver;				//Whether the program wants to end itself
	char m_graphArray[20][78];	//The printable graph
	int m_day = 0;						//Current day
	int m_arrTargetDay[3];			//Used when converting from char to int
	int m_targetDayLength = 1;	//Used to assist when converting from char to int
	int m_targetDay;					//Used when fast forwarding

	Companies* m_companies;		//For creating companies on the heap

	Player m_player;					//Reference to the player
};
