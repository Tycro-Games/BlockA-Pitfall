#include "precomp.h"
#include "AABB.h"


//found this simple aabb here: https://youtu.be/ENuk9HgeTiI?si=wfi6SQaCQVDyR6QN&t=398
bool AABB::BoxCollides(const Box& a, const  Box& b)
{
	for (int i = 0; i < 2; i++)
	{
		if (a.min.cell[i] > b.max.cell[i])
			return false;
		if (a.max.cell[i] < b.min.cell[i])
			return false;
	}

	return true;
}

bool AABB::CircleCollides(const Circle& a, const Circle& b)
{
	const float2 dist = a.c - b.c;//get the distance between the circles
	//compare it to the radius
	return (dist.x <= a.r + b.r) &&
		(dist.y <= a.r + b.r);
}



bool AABB::InsideB(const Box& a, const Box& b)
{
	return (a.min.x >= b.min.x && a.min.y >= b.min.y
		&& a.max.x <= b.max.x && a.max.y <= b.max.y);
}
//returns the AABB at the position pos
Box AABB::At(float2 pos, const Box& b)
{
	return Box{ pos + b.min, pos + b.max };
}
Circle AABB::At(float2 pos, const Circle& b)
{
	return { pos + b.c, b.r };
}
