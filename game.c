#include "game.h"

struct Game GameConstructor(bool* playGame)
{
	struct Game game;

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

		// Set velocity to 0
		struct Velocity platformVel = { (-1 * rand()) * 5.0, 0.0 };

		game.platforms[i] = PlatformConstructor(DEFAULT, platformPos, platformVel);
	}

	game.topOfScreen = screenHeight;

	return game;
}

void Game_update(struct Game* game)
{
	// Check for keyboard left or right inputs
	Game_updateInputs(game);

	// Update platforms
	for (int i = 0; i < 10; ++i)
	{
		Platform_update(&(game->platforms[i]));
	}

	// Check if there is a player collision with platform
	bool platformCollision = Game_checkPlatformCollisions(game);

	// Update player
	Player_update(&(game->player), game->rightArrow, game->leftArrow, platformCollision);

	// Check if player has fallen
	if (game->player.pos.y + game->player.boundingBox.height < game->topOfScreen - screenHeight)
	{
		*(game->playGame) = false;
		return;
	}

	// Update topOfScreen if player is too high
	if (game->player.pos.y > game->topOfScreen - (screenHeight / 3.0))
	{
		game->topOfScreen = game->player.pos.y + (screenHeight / 3.0);

		// Check if any platforms are out of view
		for (int i = 0; i < 10; ++i)
		{
			struct Platform currPlatform = game->platforms[i];
			double platformTop = currPlatform.pos.x + currPlatform.boundingBox.height;

			if (platformTop < game->topOfScreen - screenHeight)
			{
				// If one is, replace it with a new platform at the top of the screen

				struct Position newPlatformPos = { rand() % screenWidth, game->topOfScreen };
				struct Velocity newPlatformVel = { (-1 * rand()) * 5.0, 0.0 };

				game->platforms[i] = PlatformConstructor(DEFAULT, newPlatformPos, newPlatformVel);
			}
		}
	}
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
	// Draw background, player, and platforms

	Game_drawBackground();

	Player_draw(&(game->player));

	for (int i = 0; i < 10; ++i)
	{
		Platform_draw(&(game->platforms[i]));
	}
}

void Game_drawBackground()
{
	// WILLIAM

	int image_width = 320; // Image width based on background_map dimensions
	int image_height = 247; // Image height based on background_map dimensions

	int start_x = (320 - image_width) / 2; // Center the image horizontally
	int start_y = (240 - image_height) / 2; // Center the image vertically

	draw_background();

	// Draw the background image
	for (int y = 0; y < image_height - 1; y++)
	{
		for (int x = 0; x < image_width; x++)
		{
			uint16_t pixel_color = background_map_2d[y][x];
			plot_pixel(start_x + x, start_y + y, pixel_color);
		}
	}

	// Free memory allocated for 2D array
	for (int i = 0; i < image_height; i++)
	{
		free(background_map_2d[i]);
	}
	free(background_map_2d);
}

bool Game_checkPlatformCollisions(struct Game* game)
{
	// If the player is moving up, platforms should not affect them
	if (game->player.vel.y < 0)
	{
		return false;
	}

	// Check for collision with platform
	for (int i = 0; i < 10; ++i)
	{
		if (rectanglesIntersect(game->player.boundingBox, game->platforms[i].boundingBox))
		{
			return true;
		}
	}
}