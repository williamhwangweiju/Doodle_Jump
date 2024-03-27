#include "player.h"

const int kPlayerWidth = 41;
const int kPlayerHeight = 40;

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
	// WILLIAM

	int image_width = 41; // Image width based on doodle_map dimensions
	int image_height = 40; // Image height based on doodle_map dimensions

	int start_x = (int)(player->pos.x);
	int start_y = (int)(player->pos.y);

	draw_doodle();

	// Draw the doodle image
	for (int y = 0; y < image_height - 1; y++)
	{
		for (int x = 0; x < image_width; x++)
		{
			uint16_t pixel_color = doodle_map_2d[y][x];
			if (pixel_color != 0)
			{
				plot_pixel(start_x + x, start_y + y, pixel_color);
			}
		}
	}

	// Free memory allocated for 2D array
	for (int i = 0; i < image_height; i++)
	{
		free(doodle_map_2d[i]);
	}
	free(doodle_map_2d);
}

void Player_update(struct Player* player, bool right, bool left)
{
	double horizSpeed = 5;
	player->vel.x = 5 * (right - left);
}