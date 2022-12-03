/* Todo:
 * -Endgame
 * -Display money with commas
 * -Have the graph show a single line on the first day or pre-run the graph for width-2 days
 * https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
 */

#include "Game.hpp"
#include <iostream>

using std::cout;
using std::cin;

int main()
{
	Game *app = new Game();
	app->Run();
	delete app;

	cout << "\n\tPress 'Enter' to exit the program.";
	cout.flush();
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return 0;
}
