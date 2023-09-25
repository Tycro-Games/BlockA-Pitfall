#include "precomp.h"
#include "Zipline.h"

void Zipline::Render(Surface* screen)
{
	if (!Camera::OnScreenPartial(pointA, coll)) //not on screen
		return;
	const float2 camPos = Camera::GetPosition();
	//TODO make this a static function
	//Lynn showed me how I could use the template line function instead of making a new one
	float x1 = 0;
	float y1 = 0;


	for (int i = -halfWidth; i < halfWidth; i++) {
		x1 = pointA.x + static_cast<float>(i) - camPos.x;
		y1 = pointA.y - camPos.y;

		const float x2 = pointB.x + static_cast<float>(i) - camPos.x;
		const float y2 = pointB.y - camPos.y;

			screen->Line(x1, y1, x2, y2, 255 << 8);
		
	}
#ifdef _DEBUG
	screen->Box(x1 - halfWidth + coll.min.x, y1 + coll.min.y, x1 - halfWidth + coll.max.x, y1 + coll.max.y, 255 << 16);
#endif

}

void Zipline::Init(float2 a, float2 b)
{
	if (a.x > b.x)
		swap(a, b);
	pointA = a;
	pointB = b;
	coll = Box{ float2{0 ,0 },pointB - pointA };

}

