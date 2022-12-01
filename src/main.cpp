#include "Game.hpp"
#include <iostream>

using std::cout;
using std::cin;

int main()
{
	Game* app = new Game();
	app->Run();
	delete app;

	cout << "\n\tPress 'Enter' to exit the program.";
	cout.flush();
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return 0;
}
