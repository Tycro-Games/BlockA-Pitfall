#pragma once

class FreemovingState final : public State
{
public:
	void OnEnter(Avatar& p) override;
	State* Update(float deltaTime) override;
	void OnExit() override;

protected:
	void SetVariables(Avatar& p) override;

private:
	Avatar* p=nullptr;
	Timer* climbTimer = nullptr;

	float2 floorPosCollider = 0;

	Input* input = nullptr;
	float2* pos = nullptr;
	float2* velocity = nullptr;
	Tilemap* floors = nullptr;
	Tilemap* ladders = nullptr;
	Rope* ropes = nullptr;
	Zipline* ziplines = nullptr;
	size_t ropeCount = 0;
	size_t ziplineCount = 0;
	Box* floorCollider = nullptr;
	Box* boxCollider = nullptr;
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
