﻿#pragma once
// added source https://studiofreya.com/3d-math-and-physics/simple-aabb-vs-aabb-collision-detection/
struct AABB
{

	AABB(float2 min, float2 max);
	AABB();
	float2 min, max;

	static bool BoxCollides(AABB a, AABB b);
	AABB At(float2 pos) const;

};
