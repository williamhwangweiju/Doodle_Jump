#include "game.h"

int main()
{
	// Get current time. Used to maintain frame rate
	int framesPerSec = 60;

	// Initialize game
	bool playGame = true;
	struct Game game = GameConstructor(framesPerSec, &playGame);

	// Game loop
	while (playGame)
	{
		Game_update(&game);
		Game_draw(&game);
	}
}
