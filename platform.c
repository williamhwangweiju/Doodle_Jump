#include "platform.h"

const int kPlatformWidth = 60;
const int kPlatformHeight = 16;

void Platform_draw(struct Platform* platform)
{
    // WILLIAM

    int image_width = 60; // Image width based on platform_map dimensions
    int image_height = 16; // Image height based on platform_map dimensions

    int start_x = (int)(platform->pos.x);
    int start_y = (int)(platform->pos.y);

    draw_platform();

    // Draw the doodle image
    for (int y = 0; y < image_height - 1; y++)
    {
        for (int x = 0; x < image_width; x++)
        {
            uint16_t pixel_color = platform_map_2d[y][x];
            if (pixel_color != 0)
            {
                plot_pixel(start_x + x, start_y + y, pixel_color);
            }
        }
    }

    // Free memory allocated for 2D array
    for (int i = 0; i < image_height; i++)
    {
        free(platform_map_2d[i]);
    }
    free(platform_map_2d);
}

void Platform_update(struct Platform* platform)
{

}