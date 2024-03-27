#pragma once

#include "helper_functions.h"
#include "globals.h"
#include "position.h"
#include "pixels.h"

enum PlatformType { DEFAULT };

extern const int kPlatformWidth;
extern const int kPlatformHeight;

struct Platform
{
	//// PUBLIC ////
	struct Position pos;
	struct Velocity vel;
	enum PlatformType type;
};

void Platform_draw(struct Platform* platform);
void Platform_update(struct Platform* platform);