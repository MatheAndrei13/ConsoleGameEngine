#include "Game.h"
#include "GameObjectsList.h"

int main()
{
	Game game = Game(L"Game", 0, 0, 0, 0);
	game.Start();

	return 0;
}