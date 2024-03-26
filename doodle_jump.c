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
void Player_draw(struct Player* player);

struct Player PlayerConstructor(struct Position startingPos)
{
	struct Player player;

	player.pos = startingPos;

	struct Velocity vel = { 0.0, 2 * kGravityConstant * screenHeight / 2 };
	player.vel = vel;

	return player;
}

void Player_draw(struct Player* player) {}

/*********************************
			PLATFORM
*********************************/

enum PlatformType { DEFAULT };

const kPlatformWidth = 0;
const kPlatformHeight = 0;

struct Platform
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
	enum PlatformType type;
};

void Platform_draw(struct Platform* platform);

void Platform_draw(struct Platform* platform) {}

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

struct Game GameConstructor(int framesPerSec, enum bool* playGame)
{
	struct Game game;

	game.framesPerSec = framesPerSec;
	game.playGame = playGame;

	// Create player object
	struct Position playerInitialPos = { screenWidth / 2, 0 };
	game.player = PlayerConstructor(playerInitialPos);

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

	// Update right attribute
	if (!game->right && key == RIGHT_MAKE)
	{
		game->right = true;
	} else if (game->right && key == RIGHT_BREAK)
	{
		game->right = false;
	}

	// Update left attribute
	if (!game->left && key == LEFT_MAKE)
	{
		game->left = true;
	} else if (game->left && key == LEFT_BREAK)
	{
		game->left = false;
	}
}

void Game_draw(struct Game* game) {}

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