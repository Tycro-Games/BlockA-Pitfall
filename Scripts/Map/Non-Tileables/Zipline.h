#pragma once

class Zipline
{
public:
	void Render(Surface* screen);
	void Init(float2 a, float2 b);
private:
	//always is the one which is the highest
	float2 pointA = 0;
	float2 pointB = 0;
	const int halfWidth = 3;
	Box coll;

};
