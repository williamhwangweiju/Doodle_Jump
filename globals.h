#pragma once

enum KeyboardCodes
{
	RIGHT_MAKE = 0xE074,
	RIGHT_BREAK = 0xF074,
	LEFT_MAKE = 0xE06B,
	LEFT_BREAK = 0xF06B
};

extern const volatile int* PS2_ptr;

extern const int screenWidth;
extern const int screenHeight;
