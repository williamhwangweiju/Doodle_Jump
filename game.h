#pragma once

#include "player.h"
#include "platform.h"

struct Game
{
	//// PRIVATE ////
	bool* playGame;
	struct Player player;
	struct Platform platforms[10];
	bool rightArrow;
	bool leftArrow;
	double topOfScreen;
};

struct Game GameConstructor(bool* playGame);
void Game_update(struct Game* game);
int Game_getKeyboardData();
void Game_updateInputs(struct Game* game);
void Game_draw(struct Game* game);
void Game_drawBackground();
bool Game_checkPlatformCollisions(struct Game* game);
struct Position world_to_screen(struct Game* game, struct Position point);
