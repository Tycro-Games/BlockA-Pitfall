#pragma once
#include "AABB.h"

class MathLibrary
{
public:
	//pos should be in screen coodinates
	static bool OnScreen(float2 pos);
	static bool OnScreen(float2 pos, AABB col);
};
