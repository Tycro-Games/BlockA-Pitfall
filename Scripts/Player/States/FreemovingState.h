#pragma once

class FreemovingState : public State
{
public:


	void OnEnter(Avatar& p) override;
	State* Update(float deltaTime) override;
	void OnExit() override;

protected:
	void SetVariables(Avatar& p) override;

private:
	const float GRAVITY = 9.8f;
	Timer* climbTimer = nullptr;

	float2 floorPos = 0;
	float climbDelay = 0;
	const float CLIMB_DELAY = 0.5f;
	const float JUMP_FORCE = 3.0f;
	Input* input = nullptr;
	float2* pos = nullptr;
	float2* velocity = nullptr;
	Tilemap* floors = nullptr;
	Tilemap* ladders = nullptr;
	Camera* cam = nullptr;
	Box* floorCollider = nullptr;
	Box* boxCollider = nullptr;
	float speed = 0;
};
