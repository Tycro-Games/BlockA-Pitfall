#pragma once

class FreemovingState final : public PlayerState
{
public:
	void OnEnter(Avatar& p) override;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;

protected:

private:



	float speed = 0;

	const float CLIMB_DELAY = 0.5f;
	const float JUMP_FORCE = 2.0f;
	const float SMALL_JUMP_FORCE = 1.0f;
	const float GRAVITY = 9.8f;
	const float HORIZONTAL_GRAVITY = 12.0f;
	const float MAX_HORIZONTAL_SPEED = 3.0f;
	const float MAX_HORIZONTAL_INPUT_SPEED = 1.0f;
	float modifierX = 1.0f;
	const float IN_AIR_MODIFIED_X = 0.25f;
	const float ON_GROUND_MODIFIED_X = 1.0f;
};
