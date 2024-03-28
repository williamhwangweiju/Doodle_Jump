#include "pixels.h"

volatile int pixel_buffer_start;

void wait_for_vsync()
{
    volatile int* pixel_ctrl_ptr = (int*)0xFF203020;
    register int status;

    *pixel_ctrl_ptr = 1; // start the synchronization process

    // Wait until the status register's S bit becomes 0
    do
    {
        status = *(pixel_ctrl_ptr + 3); // read status register
    } while ((status & 0x01) != 0); // check S bit
}

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int* one_pixel_address;

    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);

    *one_pixel_address = line_color;
}

void clear_screen() 
{
    int x, y;

    for (y = 0; y < 240; y++) {
        for (x = 0; x < 320; x++) {
            plot_pixel(x, y, 0);
        }
    }
}
