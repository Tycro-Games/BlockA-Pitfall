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
	const float2 camPos = Camera::GetPosition();
	for (int i = -halfWidth; i < halfWidth; i++) {
		const float x1 = fixedPoint.x + static_cast<float>(i) - camPos.x;
		const float y1 = fixedPoint.y  - camPos.y;

		const float x2 = movingPoint.x + static_cast<float>(i) - camPos.x;
		const float y2 = movingPoint.y  - camPos.y;
		screen->Line( x1, y1, x2, y2, 255 << 16);
	}
	
}

void Rope::Update(float deltaTime)
{
	//got helped for this formula from Lynn 230137
	double timeElapsed = cos(t->elapsed() * frq) * amp;
	const float x = sin(timeElapsed) * len;
	const float y = cos(timeElapsed) * len;
	movingPoint = fixedPoint + float2{ x,y };
}

void Rope::Init(float2 _fixedPoint)
{
	fixedPoint = _fixedPoint;
}
