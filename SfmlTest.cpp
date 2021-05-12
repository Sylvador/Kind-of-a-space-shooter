#include <cstdlib>
#include "Game.h"

int main()
{
	srand(time(NULL));
	Game* game;
	game = new Game;
	game->run();
	return 0;
}