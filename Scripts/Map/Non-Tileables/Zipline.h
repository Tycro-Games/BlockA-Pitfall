#pragma once

class Zipline : public Entity
{
public:
	void DebugDraw(Surface* screen, float2 camPos) const;
	void Render(Surface* screen) override;
	void Init(float2 a, float2 b);
	bool GetOnScreen() const;
	void Update(float deltaTime) override;

	void GetStartEnd(float2& start, float2& end) const;
	~Zipline() override;

private:
	//always is the one which is the highest
	float2 pointA = 0;
	float2 pointB = 0;
	Box coll;
	bool onScreen = false;
};
