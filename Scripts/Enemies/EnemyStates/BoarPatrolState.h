#pragma once

class BoarPatrolState : public BoarState
{
public:
	~BoarPatrolState() override = default;
	void OnEnter() override;
	BoarState* TurnBack(Boar* boar) const;
	float GetHeading() const;
	BoarState* Update(Boar* boar, float deltaTime) override;
	void OnExit() override;
private:
	float2 originalPos = -1;
	float2 desiredPos = -1;
	const float SPEED = 0.7f;
	const float STOP_DELAY = 4.0f;

};
