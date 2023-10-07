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
