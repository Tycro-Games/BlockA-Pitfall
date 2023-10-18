#pragma once

class Rope : public Entity
{
public:
	Rope();
	~Rope() override;

	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	void Init(float2 _fixedPoint);
	bool GetOnScreen() const;
	static float2 GetMovingPartAtTime(float2 startPoint, float timeElapsed, const float leng);
	float2 GetMovingPart() const;
	float2* pGetMovingPart();

private:
	float2 points[4] = {};
	const float len[3] = {100.0f, 75.0f, 25.0f};
	const float lenMultiplier = 0.6f;
	const float multipler[3] = {0.7f, 1.2f, 2.0f};
	const uint resolution = 25;
	float totalLen = 0;
	const float frq = 1.8f;
	const float amp = 100.0f;
	const int halfWidth = 3;
	Timer* t = nullptr;
	Box coll;
	bool onScreen = false;
	float timeOffset = 0;
};
