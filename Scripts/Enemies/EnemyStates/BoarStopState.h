#pragma once

class BoarStopState: public BoarState
{
public:
	~BoarStopState() override = default;
	void OnEnter() override;
	BoarState* Update(Boar* boar, float deltaTime) override;
	void OnExit() override;
	void SetHeading(float _heading);

	void SetOriginalPos(const float2& _originalPos);

private:
	float2 originalPos = 0;
	const float STOP_TIME = .70f;
	float heading = 0;
	
};
