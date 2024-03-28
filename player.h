#pragma once

#include "helper_functions.h"
#include "globals.h"
#include "position.h"
#include "pixels.h"

extern const int kPlayerWidth;
extern const int kPlayerHeight;

struct Player
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
	struct Rectangle boundingBox;
};

struct Player PlayerConstructor();
void Player_draw(struct Player* player);
void Player_update(struct Player* player, bool right, bool left, bool platformCollision);