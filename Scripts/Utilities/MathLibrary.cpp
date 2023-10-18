#include "precomp.h"
#include "MathLibrary.h"


float2 MathLibrary::CubicBezierCurve(const float2& a, const float2& b, const float2& c, const float2& d, float t)
{
	return a * (-(t * t * t) + 3 * t * t - 3 * t + 1)
		+ b * (3 * t * t * t - (6 * t * t) + (3 * t))
		+ c * (-3 * t * t * t + 3 * t * t)
		+ d * t * t * t;
}

//from https://math.stackexchange.com/questions/1360891/find-quadratic-bezier-curve-equation-based-on-its-control-points
float2 MathLibrary::QuadraticBezierCurve(const float2& a, const float2& b, const float2& c, float t)
{
	return (1.0f - t) * (1.0f - t) * a + 2 * t * (1.0f - t) * b + (t * t) * c;
}

float MathLibrary::Sign(float value)
{
	if (value > 0)
		return 1.0f;

	return -1.0f;
}

//second paramater is assumed to be a sprite with animation frames
bool MathLibrary::PixelCollision(Surface* a, Sprite* b, int2 screenStartA, int2 screenStartB)
{
	const int2 screenEndA = {screenStartA.x + a->width, screenStartA.y + a->height};
	const int2 screenEndB = {screenStartB.x + b->GetWidth(), screenStartB.y + b->GetHeight()};

	//find the pixels coordinates that might collide
	int2 minIntersection;
	int2 maxIntersection;
	minIntersection.x = max(screenStartA.x, screenStartB.x);
	minIntersection.y = max(screenStartA.y, screenStartB.y);


	maxIntersection.x = min(screenEndA.x, screenEndB.x);
	maxIntersection.y = min(screenEndA.y, screenEndB.y);
	//compute the amount so we start on the same pixel
	const int addBX = abs(minIntersection.x - screenStartB.x);
	const int addBY = abs(minIntersection.y - screenStartB.y);

	const int addAX = abs(minIntersection.x - screenStartA.x);
	const int addAY = abs(minIntersection.y - screenStartA.y);

	uint* pixelSA = a->pixels + addAX + addAY * a->width;
	uint* pixelSB = b->GetBuffer() + addBX + addBY * b->GetWidth() * b->Frames();

	const int w = maxIntersection.x - minIntersection.x;
	const int h = maxIntersection.y - minIntersection.y;

	a->ClearOnlyNonTransparent(BLUE);
	b->GetSurface()->ClearOnlyNonTransparent(GREEN);
	bool collide = false;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			//if both pixels are not transparent
			uint* cA = &pixelSA[j + i * a->width];
			uint* cB = &pixelSB[j + i * b->GetWidth() * b->Frames()];
			if (*cA != 0 && *cB != 0)
			{
				*cA = RED;
				*cB = RED;
				//return true;
				collide = true;
			}
		}
	}
	return collide;
}
