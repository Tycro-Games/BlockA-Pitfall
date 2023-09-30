#pragma once
class ClimbingState : public PlayerState
{
public:

	void OnEnter(Avatar& p) override;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;
	PlayerState* ToTheEndOfTheLadder(float deltaTime);

protected:
private:
	float currentTime = 0;
	float totalTimeToClimb = 0.3f;
	float2 originalPlayerPos = 0;
	float2 floorPos = { -1.0f };
	const float CLIMBING_JUMP_FORCE = 1.4f;

};

