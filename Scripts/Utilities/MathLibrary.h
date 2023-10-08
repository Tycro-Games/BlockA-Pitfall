#pragma once


class MathLibrary
{
public:
	static float2 CubicBezierCurve(const float2& a, const float2& b, const float2& c, const float2& d, float t);
	static float2 QuadraticBezierCurve(const float2& a, const float2& b, const float2& c, float t);
	static float Sign(float value);
};
