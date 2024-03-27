#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "helper_functions.h"

enum bool{ false = 0, true = 1 };

enum KeyboardCodes
{
	RIGHT_MAKE = 0xE074,
	RIGHT_BREAK = 0xF074,
	LEFT_MAKE = 0xE06B,
	LEFT_BREAK = 0xF06B
};

const volatile int* PS2_ptr = (int*)0xFF200100;

const int screenWidth = 400;
const int screenHeight = 500;

/*********************************
			PIXELS
*********************************/
volatile int pixel_buffer_start;

void wait_for_vsync() {
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
    register int status;

    *pixel_ctrl_ptr = 1; // start the synchronization process

    // Wait until the status register's S bit becomes 0
    do {
        status = *(pixel_ctrl_ptr + 3); // read status register
    } while ((status & 0x01) != 0); // check S bit
}

void plot_pixel(int x, int y, short int line_color) {
    volatile short int *one_pixel_address;
        
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
        
    *one_pixel_address = line_color;
}

/*********************************
			POSITION
*********************************/

const kGravityConstant = 9.81;

struct Position
{
	double x;
	double y;
};

struct Velocity
{
	double x;
	double y;
};

/*********************************
			PLAYER
*********************************/

const int kPlayerWidth = 0; // WILLIAM
const int kPlayerHeight = 0; // WILLIAM

struct Player
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
};

struct Player PlayerConstructor();
void Player_draw(struct Player* player);

struct Player PlayerConstructor()
{
	struct Player player;

	struct Position startingPos = { screenWidth / 2, 0 };
	player.pos = startingPos;

	struct Velocity vel = { 0.0, 2 * kGravityConstant * screenHeight / 2 };
	player.vel = vel;

	return player;
}

void Player_draw(struct Player* player) {
	// WILLIAM

	int image_width = 41; // Image width based on doodle_map dimensions
	int image_height = 40; // Image height based on doodle_map dimensions

	int start_x = (int)(player->pos.x);
    	int start_y = (int)(player->pos.y);
	
	draw_doodle();

	// Draw the doodle image
    for (int y = 0; y < image_height - 1; y++) {
        for (int x = 0; x < image_width; x++) {
            uint16_t pixel_color = doodle_map_2d[y][x];
            if (pixel_color != 0) {
            plot_pixel(start_x + x, start_y + y, pixel_color);
			}
        }
    }

    // Free memory allocated for 2D array
    for (int i = 0; i < image_height; i++) {
        free(doodle_map_2d[i]);
    }
    free(doodle_map_2d);
}

/*********************************
			PLATFORM
*********************************/

enum PlatformType { DEFAULT };

const int kPlatformWidth = 0; // WILLIAM
const int kPlatformHeight = 0; // WILLIAM

struct Platform
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
	enum PlatformType type;
};

void Platform_draw(struct Platform* platform);

void Platform_draw(struct Platform* platform) {
	// WILLIAM

	int image_width = 60; // Image width based on platform_map dimensions
	int image_height = 16; // Image height based on platform_map dimensions

	int start_x = (int)(platform->pos.x);
    int start_y = (int)(platform->pos.y);
	
	draw_platform();

	// Draw the doodle image
    for (int y = 0; y < image_height - 1; y++) {
        for (int x = 0; x < image_width; x++) {
            uint16_t pixel_color = platform_map_2d[y][x];
            if (pixel_color != 0) {
            plot_pixel(start_x + x, start_y + y, pixel_color);
			}
        }
    }

    // Free memory allocated for 2D array
    for (int i = 0; i < image_height; i++) {
        free(platform_map_2d[i]);
    }
    free(platform_map_2d);
}

/*********************************
			GAME
*********************************/

struct Game
{
	//// PRIVATE ////
	enum bool* playGame;
	int framesPerSec;
	struct Player player;
	struct Platform platforms[10];
	enum bool right;
	enum bool left;
};

struct Game GameConstructor(int framesPerSec, enum bool* playGame);
void Game_update(struct Game* game);
int Game_getKeyboardData();
void Game_updatePlayerDirection(struct Game* game);
void Game_draw(struct Game* game);
void Game_drawBackground();

struct Game GameConstructor(int framesPerSec, enum bool* playGame)
{
	struct Game game;

	game.framesPerSec = framesPerSec;
	game.playGame = playGame;

	// Create player object
	game.player = PlayerConstructor();

	// No keyboard inputs by default
	game.right = false;
	game.left = false;

	// Generate platforms positions randomly
	for (int i = 0; i < 10; ++i)
	{
		// For initial platforms, height should be within top two-thirds of screen
		struct Position platformPos = {rand() % screenWidth, (screenHeight / 3) + rand() % (screenHeight - (screenHeight / 3))};
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
	Game_updatePlayerDirection(game);
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

void Game_updatePlayerDirection(struct Game* game)
{
	int key = Game_getKeyboardData();

	// Update right arrow
	if (!game->right && key == RIGHT_MAKE)
	{
		game->right = true;
	} else if (game->right && key == RIGHT_BREAK)
	{
		game->right = false;
	}

	// Update left arrow
	if (!game->left && key == LEFT_MAKE)
	{
		game->left = true;
	} else if (game->left && key == LEFT_BREAK)
	{
		game->left = false;
	}
}

void Game_draw(struct Game* game) {
	Game_drawBackground();

	Player_draw(&(game->player));

	for (int i = 0; i < 10; ++i)
	{
		Platform_draw(&(game->platforms[i]));
	}
}

void Game_drawBackground() {
	// WILLIAM

	int image_width = 320; // Image width based on background_map dimensions
    int image_height = 247; // Image height based on background_map dimensions

	int start_x = (320 - image_width) / 2; // Center the image horizontally
    int start_y = (240 - image_height) / 2; // Center the image vertically

	draw_background();

	// Draw the background image
    for (int y = 0; y < image_height - 1; y++) {
        for (int x = 0; x < image_width; x++) {
            uint16_t pixel_color = background_map_2d[y][x];
            plot_pixel(start_x + x, start_y + y, pixel_color);
        }
    }

    // Free memory allocated for 2D array
    for (int i = 0; i < image_height; i++) {
        free(background_map_2d[i]);
    }
    free(background_map_2d);
}

/*********************************
			MAIN
*********************************/

int main()
{
	// Get current time. Used to maintain frame rate
	int framesPerSec = 60;

	// Initialize game
	enum bool playGame = true;
	struct Game game = GameConstructor(framesPerSec, &playGame);

	// Game loop
	while (playGame)
	{
		Game_update(&game);
		Game_draw(&game);
	}
}
