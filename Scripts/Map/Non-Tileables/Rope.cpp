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
	float2 p0 = points[0] - camPos;
	float2 p1 = points[1] - camPos;
	float2 p2 = points[2] - camPos;
	float2 p3 = points[3] - camPos;
	screen->BezierCurve(255 << static_cast<uint>(t->elapsed()) % 16, p0, p1, p2, p3, resolution);
	/*
		for (int j = 0; j < 3; j++) {


			for (int i = -halfWidth; i < halfWidth; i++) {
				x1 = points[j].x + static_cast<float>(i) - camPos.x;
				y1 = points[j].y - camPos.y;

				const float x2 = points[j + 1].x + static_cast<float>(i) - camPos.x;
				const float y2 = points[j + 1].y - camPos.y;

				screen->Line(x1, y1, x2, y2, 255 << 16);

			}
		}*/
#ifdef _DEBUG
	const float x1 = points[0].x - camPos.x;
	const float y1 = points[0].y - camPos.y;
	screen->Box(x1 - halfWidth + coll.min.x, y1 + coll.min.y, x1 - halfWidth + coll.max.x, y1 + coll.max.y, 255 << 16);
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
	//TODO make this start with a random value
	for (int i = 1; i < 4; i++) {
		float timeElapsed = cos(timeOffset + t->elapsed() * frq) * amp;

		points[i] = GetMovingPartAtTime(points[i - 1], timeElapsed * multipler[i - 1], len[i - 1]);
	}
}

void Rope::Init(float2 _fixedPoint)
{
	InitSeed(0);
	timeOffset = RandomFloat() * 100;
	frq = 1.0f + clamp(RandomFloat() + 0.8f, 0.0f, 1.0f);
	amp = clamp(RandomFloat() + 0.4f, 0.0f, 1.0f);
	//cout << timeOffset;
	points[0] = _fixedPoint;
	for (int i = 0; i < 3; i++)
		totalLen += len[i];
	coll = Box{ -float2{totalLen ,0 }, float2{totalLen ,totalLen  } };
}

bool Rope::GetOnScreen() const
{
	return onScreen;

}
