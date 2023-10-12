#pragma once

class Rock
{
public:
	void Init(const float2& _pos, const float2& _dir);
	~Rock();
	const float2& GetPosition() const;
	void Update(float deltaTime);
	const Box& GetBoxCollider() const;
	bool GetActive() const;
	void SetActive(bool val);
private:
	float2 dir = 0;
	float2 pos = 0;
	bool active = false;
	const float SPEED = 450.0f;
	Timer* timer = nullptr;
	const float TIME_ALIVE = 3.0f;
	const float DISTANCE_TO_ENEMY = 5.0f;
	Box col;
};
