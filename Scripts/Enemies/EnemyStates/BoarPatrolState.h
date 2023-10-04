#pragma once

class BoarPatrolState : public BoarState
{
public:
	~BoarPatrolState() override = default;
	void OnEnter() override;
	BoarState* Update(Boar* boar, float deltaTime) override;
	void OnExit() override;
	const float SPEED = 0.7f;
	float2 originalPos = -1;
	float2 desiredPos = -1;
	float t = 0;
};
