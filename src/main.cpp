#include "Game.h"

int main()
{
	Game* app = new Game();
	app->Run();
	delete app;

	std::cout << std::endl << "\tPress 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();

	return 0;
}
