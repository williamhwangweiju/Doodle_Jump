#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Variables
extern uint16_t **doodle_map_2d;
extern uint16_t **background_map_2d;

// Function prototypes
extern void plot_pixel(int x, int y, short int line_color);
extern void draw_background();
extern void convert_to_2d(uint16_t **matrix, const uint8_t *arr, int row, int col);
extern void draw_doodle(int x, int y);