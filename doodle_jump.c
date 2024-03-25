#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRAVITY_CONSTANT 9.81

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

struct Player
{
	//// PUBLIC ////
	Player() {};

	Player(struct Position startingPos)
	{
		pos = startingPos;
		vel = { 0.0, 0.0 };
	}

	struct Position pos;
	struct Velocity vel;

	void update() {};
	void draw() {};

	Player& operator=(const Player& rhs)
	{
		this->pos = rhs.pos;
		this->vel = rhs.vel;

		return *this;
	}

	//// PRIVATE ////
	const double width_priv = 0;
	const double height_priv = 0;
};

enum PlatformType { DEFAULT };

struct Platform
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
	enum PlatformType type;

	//// PRIVATE ////
	const double width_priv;
	const double height_priv;
};

struct Game
{
	//// PUBLIC ////
	Game(int& _framesPerSec, bool& _playGame)
	{
		framesPerSec = _framesPerSec;
		playGame = _playGame;

		// Create player object
		struct Position playerInitialPos = { screenWidth / 2, 0 };
		player = struct Player(playerInitialPos);

		// Generate initial platforms
		int numPlatforms = 10;
		platforms = getNewPlatforms(numPlatforms);

		// Generate platforms positions randomly
		for (int i = 0; i < numPlatforms; ++i)
		{
			// For initial platforms, height should be within top two-thirds of screen
			struct Position platformPos = { rand() % screenWidth, (screenHeight / 3) + rand() % (screenHeight - (screenHeight / 3)) };
			platforms[i].pos = platformPos;
		}
	}

	//// PRIVATE ////
	bool& playGame;
	int& framesPerSec;
	struct Player player;
	struct Platform* platforms;
	const int screenHeight = 533;
	const int screenWidth = 400;

	struct Platform* getNewPlatforms(int numPlatforms)
	{
		return malloc(numPlatforms * sizeof(struct Platform));
	}
};

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