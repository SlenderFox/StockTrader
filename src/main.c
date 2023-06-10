#include <stdbool.h> // bool, true, false
#include <stdio.h> // printf

#include "game.h"

bool running = false;

// TODO: Add new game functionality

int
main (int argc, char *args[])
{
	do
	{
		st_game_run ();
	}
	while (running);

	printf ("Bye\n");
	return 0;
}
