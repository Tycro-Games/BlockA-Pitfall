#pragma once

struct AABB
{

	AABB(float2 min, float2 max);
	AABB();
	float2 min, max;

	static bool Collides(AABB a, AABB b);
	

};
