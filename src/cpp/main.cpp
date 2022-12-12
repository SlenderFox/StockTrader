/* Todo:
 * -Endgame
 * -Display money with commas
 * -Have the graph show a single line on the first day or pre-run the graph for width-2 days
 * https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
 */

#include "game.hpp"
#include <iostream>

using std::cout;
using std::cin;

int main(int argc, char **args)
{
	stockTrader::game *app = new stockTrader::game();
	app->run();
	delete app;
	return 0;
}
