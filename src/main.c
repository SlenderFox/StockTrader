#include <stdio.h> // printf

#include "game.h"

bool running = true;

// TODO: Add new game functionality

int
main (int argc, char *args[])
{
	while (running)
	{
		if (st_game_run ())
		{
			running = false;
		}
	}

	printf ("Bye\n");
	return 0;
}
