#include "game.h"

int main()
{
	// Initialize game
	bool playGame = true;
	struct Game game = GameConstructor(&playGame);

	// Game loop
	Game_update(&game);
	while (playGame)
	{
		Game_draw(&game);
		Game_update(&game);
	}
}
