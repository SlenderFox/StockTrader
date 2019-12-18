/*----------------------------------------------
	File Name: Main.cpp
	Author: Dylan Glenister
	Modified: 17/12/19 (dd/mm/yy)
----------------------------------------------*/

#include "Game.h"
#include <iostream>

int main()
{
	Game* game = new Game();

	// Calls startup and exits if there is an error
	if (!game->Startup())
		return 0;

	// Game loop
	while (!game->IsGameOver())
	{
		game->Update();
		game->Draw();
		game->UserInput();
	} // End game loop

	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();

	return 0;
}
