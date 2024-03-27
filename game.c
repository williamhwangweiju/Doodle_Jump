#include "game.h"

struct Game GameConstructor(int framesPerSec, bool* playGame)
{
	struct Game game;

	game.framesPerSec = framesPerSec;
	game.playGame = playGame;

	// Create player object
	game.player = PlayerConstructor();

	// No keyboard inputs by default
	game.rightArrow = false;
	game.leftArrow = false;

	// Generate platforms positions randomly
	for (int i = 0; i < 10; ++i)
	{
		// For initial platforms, height should be within top two-thirds of screen
		struct Position platformPos = { rand() % screenWidth, (screenHeight / 3) + rand() % (screenHeight - (screenHeight / 3)) };
		game.platforms[i].pos = platformPos;

		// Set velocity to 0
		struct Velocity platformVel = { 0.0, 0.0 };
		game.platforms[i].vel = platformVel;

		// Set type to default
		game.platforms[i].type = DEFAULT;
	}


}

void Game_update(struct Game* game)
{
	// Check for keyboard left or right inputs
	Game_updateInputs(game);

	for (int i = 0; i < 10; ++i)
	{
		Platform_update(&(game->platforms[i]));
	}

	Game_checkCollisions(game);

	Player_update(&(game->player), game->rightArrow, game->leftArrow);
}

int Game_getKeyboardData()
{
	int keyboardData = *(PS2_ptr);
	int RVALID = (keyboardData & 0x8000);

	if (RVALID != 0)
	{
		return keyboardData & 0xff;
	}
}

void Game_updateInputs(struct Game* game)
{
	int key = Game_getKeyboardData();

	// Update right arrow
	if (!game->rightArrow && key == RIGHT_MAKE)
	{
		game->rightArrow = true;
	} else if (game->rightArrow && key == RIGHT_BREAK)
	{
		game->rightArrow = false;
	}

	// Update left arrow
	if (!game->leftArrow && key == LEFT_MAKE)
	{
		game->leftArrow = true;
	} else if (game->leftArrow && key == LEFT_BREAK)
	{
		game->leftArrow = false;
	}
}

void Game_draw(struct Game* game)
{
	Game_drawBackground();

	Player_draw(&(game->player));

	for (int i = 0; i < 10; ++i)
	{
		Platform_draw(&(game->platforms[i]));
	}
}

void Game_drawBackground()
{
	
}

void Game_checkCollisions(struct Game* game)
{
	// Check for player collisions with platforms
	if (game->player.vel.y > 0)
	{
		return;
	}


}