#include "precomp.h"
#include "MathLibrary.h"

#include "AABB.h"

bool MathLibrary::OnScreen(float2 pos)
{
	return pos.y >= 0 && pos.x >= 0 &&
		pos.y < SCRHEIGHT && pos.x < SCRWIDTH;
}

bool MathLibrary::OnScreen(float2 pos, AABB col)
{
	float2 min;
	min.x = pos.x - col.min.x;
	min.y = pos.y - col.min.y;

	float2 max;
	max.x = pos.x + col.max.x;
	max.y = pos.y + col.max.y;


	return min.x >= 0 && min.y >= 0 &&
		max.y < SCRHEIGHT && max.x < SCRWIDTH;
}
