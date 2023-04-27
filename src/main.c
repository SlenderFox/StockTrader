#include <stdbool.h> // bool, true, false
#include <assert.h> // assert
#include <stdio.h> // printf

#include "game.h"

bool running = true;

int
main (int argc, char *args[])
{
	while (running)
	{
		if (!st_game_run ())
		{
			running = false;
		}
	}

	printf ("Bye\n");
	return 0;
}
