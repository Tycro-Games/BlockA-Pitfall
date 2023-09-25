#include "precomp.h"
#include "Zipline.h"

void Zipline::Render(Surface* screen)
{
	const float2 camPos = Camera::GetPosition();
	//TODO make this a static function
	for (int i = -halfWidth; i < halfWidth; i++) {
		const float x1 = pointA.x + static_cast<float>(i) - camPos.x;
		const float y1 = pointA.y - camPos.y;

		const float x2 = pointB.x + static_cast<float>(i) - camPos.x;
		const float y2 = pointB.y - camPos.y;
		screen->Line(x1, y1, x2, y2, 255 << 8);
	}
}

void Zipline::Init(float2 a, float2 b)
{
	if (a.x > b.x)
		swap(a, b);
	pointA = a;
	pointB = b;
}

