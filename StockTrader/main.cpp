/*----------------------------------------------
	Filename: Main.cpp
	Author: Dylan Glenister
	Modified: 25/02/21 (dd/mm/yy)
----------------------------------------------*/

#include "Game.h"
#include <iostream>

int main()
{
	Game* app = new Game();

	// Calls startup and exits if there is an error
	if (app->Startup())
	{
		// Game loop
		while (!app->GetGameOver())
		{
			app->Update();
			app->Draw();
			app->UserInput();
		}
	}

	std::cout << std::endl << "\tPress 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();

	return 0;
}
