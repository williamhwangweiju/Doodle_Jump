#include "player.h"

const int kPlayerWidth = 0;
const int kPlayerHeight = 0;

struct Player PlayerConstructor()
{
	struct Player player;

	struct Position startingPos = { screenWidth / 2, screenHeight / 2 }; // TO BE CHANGED
	player.pos = startingPos;

	struct Velocity vel = { 0.0, 2 * kGravityConstant * screenHeight / 2 };
	player.vel = vel;

	return player;
}

void Player_draw(struct Player* player)
{
	
}

void Player_update(struct Player* player, bool right, bool left)
{
	double horizSpeed = 5;
	player->vel.x = 5 * (right - left);
}