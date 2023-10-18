#pragma once

class BoarTurnState : public BoarState
{
public:
	~BoarTurnState() override = default;
	void OnEnter() override;
	BoarState* Update(Boar* boar, float deltaTime) override;
	void OnExit() override;
	void SetHeading(float _heading);
	void SetOriginalPos(const float2& _originalPos);

private:
	float heading = 0;
	const float turnAmount = 10.0f;
	float2 originalPos = 0;
	float2 desiredPos = 0;
	const float SPEED = 20.0f;
};
