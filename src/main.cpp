/* Todo:
 * -Endgame
 * -Display money with commas
 * -Have the graph show a single line on the first day or pre-run the graph for width-2 days
 * https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
 */

//#include "game.hpp"
#include "io.hpp"
#include <iostream>

using std::cout;
using std::cin;

int main(int argc, char **args)
{
	//stockTrader::game *app = new stockTrader::game();
	//app->run();
	//delete app;

	stockTrader::io *console = stockTrader::io::get();

	for (int i = 0; i < 10; ++i)
	{
		console->update(i);
		console->draw();
		console->swapBuffers();
	}

	delete console;

	//cout << "\n\tPress 'Enter' to exit the program.";
	//cout.flush();
	//cin.clear();
	//cin.ignore(cin.rdbuf()->in_avail());
	//cin.get();

	return 0;
}
