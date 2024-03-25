#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int screenWidth = 400;
const int screenHeight = 500;

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

const kPlayerWidth = 0;
const kPlayerHeight = 0;

struct Player
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
};

struct Player PlayerConstructor(struct Position startingPos);

struct Player PlayerConstructor(struct Position startingPos)
{
	struct Player player;

	player.pos = startingPos;

	struct Velocity vel = { 0.0, 0.0 };
	player.vel = vel;

	return player;
}

/*********************************
			PLATFORM
*********************************/

const kPlatformWidth = 0;
const kPlatformHeight = 0;

struct Platform
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
	enum PlatformType type;
};

/*********************************
			GAME
*********************************/

struct Game
{
	//// PRIVATE ////
	bool* playGame;
	int* framesPerSec;
	struct Player player;
	struct Platform* platforms;
};

struct Game GameConstructor(int* framesPerSec, bool* playGame);
struct Platform* getNewPlatforms(int numPlatforms);

struct Game GameConstructor(int* framesPerSec, bool* playGame)
{
	struct Game game;

	game.framesPerSec = framesPerSec;
	game.playGame = playGame;

	// Create player object
	struct Position playerInitialPos = { screenWidth / 2, 0 };
	game.player = PlayerConstructor(playerInitialPos);

	// Generate initial platforms
	int numPlatforms = 10;
	game.platforms = getNewPlatforms(numPlatforms);

	// Generate platforms positions randomly
	for (int i = 0; i < numPlatforms; ++i)
	{
		// For initial platforms, height should be within top two-thirds of screen
		struct Position platformPos = { rand() % screenWidth, (screenHeight / 3) + rand() % (screenHeight - (screenHeight / 3)) };
		game.platforms[i].pos = platformPos;
	}
}

struct Platform* getNewPlatforms(int numPlatforms)
{
	return malloc(numPlatforms * sizeof(struct Platform));
}

/*********************************
			MAIN
*********************************/

int main()
{
	printf("Doodle Jump!");

	// Seed RNG
	srand(time(NULL));

	// Get current time. Used to maintain frame rate
	time_t previous;
	time(&previous);
	int framesPerSec = 60;

	// Initialize game
	bool playGame = true;
	struct Game game(framesPerSec, playGame);

	// Game loop
	while (playGame)
	{

	}
}