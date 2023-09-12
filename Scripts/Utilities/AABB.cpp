#include "precomp.h"
#include "AABB.h"

AABB::AABB(float2 min, float2 max) :
	min(min), max(max)
{

}

AABB::AABB()
= default;

bool AABB::BoxCollides(AABB a, AABB b)
{
	return (a.min.x <= b.max.x && a.min.y <= b.max.y
		&& a.max.x >= b.min.x && a.max.y >= b.min.y);
}
//returns the AABB at the position pos
AABB AABB::At(float2 pos) const
{
	return { pos + min, pos + max };
}
