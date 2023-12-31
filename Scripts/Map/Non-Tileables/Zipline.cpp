﻿#include "precomp.h"
#include "Zipline.h"


void Zipline::DebugDraw(Surface* screen, const float2 camPos) const
{
	const int x1 = static_cast<int>(-camPos.x + coll.min.x);
	const int y1 = static_cast<int>(-camPos.y + coll.min.y);

	const int x2 = static_cast<int>(-camPos.x + coll.max.x);
	const int y2 = static_cast<int>(-camPos.y + coll.max.y);

	screen->Box(x1, y1, x2, y2, GREEN);
}

void Zipline::Render(Surface* screen)
{
	if (!onScreen) return;
	const float2 camPos = Camera::GetPosition();


	const float x1 = pointA.x - camPos.x;
	const float y1 = pointA.y - camPos.y;

	const float x2 = pointB.x - camPos.x;
	const float y2 = pointB.y - camPos.y;

	screen->Line(x1, y1, x2, y2, GREEN);

#ifdef _DEBUG

	DebugDraw(screen, camPos);

#endif
}

void Zipline::Init(float2 a, float2 b)
{
	if (a.y > b.y)
		swap(a, b);
	pointA = a;
	pointB = b;
	const float minX = min(a.x, b.x);
	const float minY = min(a.y, b.y);

	const float maxX = max(a.x, b.x);
	const float maxY = max(a.y, b.y);
	coll = Box{float2{minX, minY}, float2{maxX, maxY}};
}

bool Zipline::GetOnScreen() const
{
	return onScreen;
}

void Zipline::Update(float deltaTime)
{
	deltaTime;
	onScreen = Camera::OnScreen(coll);
}

void Zipline::GetStartEnd(float2& start, float2& end) const
{
	start = pointA;
	end = pointB;
}

Zipline::~Zipline() = default;
