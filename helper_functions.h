#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Variables
extern uint16_t** platform_map_2d;
extern uint16_t** doodle_map_2d;
extern uint16_t** background_map_2d;

// Function prototypes
extern void convert_to_2d(uint16_t** matrix, const uint8_t* arr, int row, int col);
extern void draw_platform();
extern void draw_doodle();
extern void draw_background();