#include "precomp.h"
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

	if (!onScreen)
		return;
	const float2 camPos = Camera::GetPosition();
	const float2 p0 = points[0] - camPos;
	const float2 p1 = points[1] - camPos;
	const float2 p2 = points[2] - camPos;
	const float2 p3 = points[3] - camPos;
	screen->BezierCurve(RED, p0, p1, p2, p3, resolution);

#ifdef _DEBUG
	const int x1 = static_cast<int>(points[0].x - camPos.x + coll.min.x);
	const int y1 = static_cast<int>(points[0].y - camPos.y + coll.min.y);

	const int x2 = static_cast<int>(points[0].x - camPos.x + coll.max.x);
	const int y2 = static_cast<int>(points[0].y - camPos.y + coll.max.y);
	screen->Box(x1, y1, x2, y2, RED);
#endif

}

float2 Rope::GetMovingPartAtTime(float2 startPoint, float timeElapsed, const float leng)
{
	const float x = sinf(timeElapsed) * leng;
	const float y = cosf(timeElapsed) * leng;
	return startPoint + float2{ x,y };
}

float2 Rope::GetMovingPart() const
{
	return points[3];
}
float2* Rope::pGetMovingPart()
{
	return &points[3];
}

void Rope::Update(float deltaTime)
{

	onScreen = Camera::OnScreen(points[0], coll);
	//got helped for this formula from Lynn 230137
	for (int i = 1; i < 4; i++) {
		const float timeElapsed = cosf(timeOffset + t->elapsedF() * frq) * amp * deltaTime;

		points[i] = GetMovingPartAtTime(points[i - 1], timeElapsed * multipler[i - 1], len[i - 1] * lenMultiplier);
	}
}

void Rope::Init(float2 _fixedPoint)
{
	//offset the function using the fixed point
	if (static_cast<int>(_fixedPoint.x) % 2 == 0) {
		timeOffset = PI;
	}
	else
		timeOffset = 0;

	points[0] = _fixedPoint;
	for (int i = 0; i < 3; i++)
		totalLen += len[i];
	coll = Box{ -float2{totalLen * lenMultiplier ,0 }, float2{totalLen * lenMultiplier  ,totalLen * lenMultiplier   } };
}

bool Rope::GetOnScreen() const
{
	return onScreen;

}
