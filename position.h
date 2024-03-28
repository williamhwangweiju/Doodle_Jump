#pragma once

#include "globals.h"
#include <stdbool.h>

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

struct Rectangle
{
	struct Position bottomLeft;
	double width;
	double height;
};

bool rectanglesIntersect(struct Rectangle rect1, struct Rectangle rect2);