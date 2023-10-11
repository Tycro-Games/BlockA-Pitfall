#pragma once

class Rock
{
public:
	void Init(const float2& _pos, const float2& _dir);
	const float2& GetPosition() const;
	void Update(float deltaTime);
	const Box& GetBoxCollider() const;
	bool GetActive() const;
	void SetActive(bool val);
private:
	float2 dir = 0;
	float2 pos = 0;
	bool active = false;
	const float SPEED = 250.0f;
	const float DISTANCE_TO_ENEMY = 10.0f;
	Box col;
};
