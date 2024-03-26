#pragma once

#include "helper_functions.h"
#include "globals.h"
#include "position.h"

extern const int kPlayerWidth;
extern const int kPlayerHeight;

struct Player
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
};

struct Player PlayerConstructor();
void Player_draw(struct Player* player);