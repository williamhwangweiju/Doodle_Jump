#include "game.h"

short int Buffer1[240][512];
short int Buffer2[240][512];

int main()
{
	
	volatile int *pixel_ctrl_ptr = (int*) 0xFF203020;

	/* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int)&Buffer1;
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer

	// Initialize game
	bool playGame = true;
	struct Game game = GameConstructor(&playGame);

	// Game loop
	Game_update(&game);
	while (playGame)
	{
		Game_draw(&game);
		Game_update(&game);

		wait_for_vsync();
		pixel_buffer_start = *(pixel_ctrl_ptr + 1);
	}

	return 0;
}
