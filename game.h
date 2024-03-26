#pragma once

#include "player.h"
#include "platform.h"

struct Game
{
	//// PRIVATE ////
	bool* playGame;
	int framesPerSec;
	struct Player player;
	struct Platform platforms[10];
	bool right;
	bool left;
};

struct Game GameConstructor(int framesPerSec, bool* playGame);
void Game_update(struct Game* game);
int Game_getKeyboardData();
void Game_updatePlayerDirection(struct Game* game);
void Game_draw(struct Game* game);
void Game_drawBackground();