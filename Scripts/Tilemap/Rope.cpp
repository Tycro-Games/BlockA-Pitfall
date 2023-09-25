﻿#include "precomp.h"
#include "Rope.h"

Rope::Rope()

{
	t = new Timer();
}

Rope::~Rope()
{
	delete t;
}

void Rope::Render(Surface* screen)
{
	if (!Camera::OnScreenPartial(fixedPoint, coll))//not on screen
		return;
	const float2 camPos = Camera::GetPosition();
	float x1 = 0;
	float y1 = 0;


	for (int i = -halfWidth; i < halfWidth; i++) {
		x1 = fixedPoint.x + static_cast<float>(i) - camPos.x;
		y1 = fixedPoint.y - camPos.y;

		const float x2 = movingPoint.x + static_cast<float>(i) - camPos.x;
		const float y2 = movingPoint.y - camPos.y;

		screen->Line(x1, y1, x2, y2, 255 << 16);

	}
#ifdef _DEBUG
	screen->Box(x1 - halfWidth + coll.min.x, y1 + coll.min.y, x1 - halfWidth + coll.max.x, y1 + coll.max.y, 255 << 16);
#endif

}

float2 Rope::GetMovingPart(double timeElapsed)
{
	const float x = sin(timeElapsed) * len;
	const float y = cos(timeElapsed) * len;
	return fixedPoint + float2{ x,y };
}

void Rope::Update(float deltaTime)
{
	//got helped for this formula from Lynn 230137
	double timeElapsed = cos(t->elapsed() * frq) * amp;
	movingPoint = GetMovingPart(timeElapsed);
}

void Rope::Init(float2 _fixedPoint)
{
	fixedPoint = _fixedPoint;

	coll = Box{ -float2{len ,0 }, float2{len ,len  } };
}
