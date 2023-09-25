#pragma once

class Zipline
{
public:
	void DrawThickerLine(Surface* screen, float2 camPos);
	void Render(Surface* screen);
	void Init(float2 a,float2 b);
private://always is the one on the left
	float2 pointA = 0;
	float2 pointB = 0;
	const int halfWidth = 3;
	Box coll;

};
