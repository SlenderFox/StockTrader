#include "Game.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	Game* app = new Game();
	app->Run();
	delete app;

	cout << endl << "\tPress 'Enter' to exit the program.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return 0;
}
