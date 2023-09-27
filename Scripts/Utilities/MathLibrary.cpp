#include "precomp.h"
#include "MathLibrary.h"


float2 MathLibrary::CubicBezierCurve(const float2& a, const float2& b,const  float2& c, const float2& d, float t)
{
	return a * (-(t * t * t) + 3 * t * t - 3 * t + 1)
		+ b * (3 * t * t * t - (6 * t * t) + (3 * t))
		+ c * (-3 * t * t * t + 3 * t * t)
		+ d * t * t * t;
}
