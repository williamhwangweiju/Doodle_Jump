#pragma once

#include "globals.h"
#include "helper_functions.h"

extern volatile int pixel_buffer_start;

void wait_for_vsync();
void plot_pixel(int x, int y, short int line_color);