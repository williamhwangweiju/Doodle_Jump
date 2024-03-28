#include "position.h"

bool rectanglesIntersect(struct Rectangle rect1, struct Rectangle rect2)
{
	// Returns true if the two rectangles intersect

	double rect1Left = rect1.bottomLeft.x;
	double rect2Left = rect2.bottomLeft.x;

	double rect1Right = rect1.bottomLeft.x + rect1.width;
	double rect2Right = rect2.bottomLeft.x + rect2.width;

	double rect1Bottom = rect1.bottomLeft.y;
	double rect2Bottom = rect2.bottomLeft.y;

	double rect1Top = rect1.bottomLeft.y + rect1.height;
	double rect2Top = rect2.bottomLeft.y + rect2.height;

	if (rect1Left < rect2Right && rect1Right > rect2Left && rect1Top > rect2Bottom && rect1Bottom < rect2Top)
	{
		return true;
	}

	return false;
}