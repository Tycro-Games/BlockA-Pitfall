#pragma once

class Rope
{
public:
	Rope();
	~Rope();

	void Render(Surface* screen);
	void Update(float deltaTime);
	void Init(float2 _fixedPoint);
	bool GetOnScreen() const;
	float2 GetMovingPartAtTime(float2 startPoint, float timeElapsed, const float leng);
	float2 GetMovingPart() const;
	float2* pGetMovingPart();

private:
	float2 points[4] = {};
	const float len[3] = { 100.0f,75.0f,25.0f };
	const float multipler[3] = { 0.7f,1.2f,2.0f };
	const float resolution = 25.0f;
	float totalLen = 0;
	float frq = .8f;
	float amp = 1.0f;
	const int halfWidth = 3;
	Timer* t;
	Box coll;
	bool onScreen = false;
	float timeOffset = 0;
};
