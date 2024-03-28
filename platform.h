#pragma once

#include "helper_functions.h"
#include "globals.h"
#include "position.h"
#include "pixels.h"

enum PlatformType { DEFAULT };

extern const int kPlatformWidth;
extern const int kPlatformHeight;
extern const double jumpSpeed;
extern const double horizSpeed;
extern const double gravity;

struct Platform
{
	//// PUBLIC ////
	enum PlatformType type;
	struct Position pos;
	struct Velocity vel;
	struct Rectangle boundingBox;
};

struct Platform PlatformConstructor(enum PlatformType type, struct Position startingPos, struct Velocity startingVel);
void Platform_draw(struct Platform* platform);
void Platform_update(struct Platform* platform);