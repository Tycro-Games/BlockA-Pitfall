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
	float2 BOX_POS = 0;
	const float RADIUS_TO_ZIPLINE = 10.0f;
	const float RADIUS_TO_ROPE = 30.0f;
	const float CLIMB_DELAY = 0.5f;
	const float JUMP_FORCE = 2.0f;
	const float GRAVITY = 9.8f;
	const float HORIZONTAL_GRAVITY = 12.0f;
	const float MAX_HORIZONTAL_SPEED = 3.0f;
	const float MAX_HORIZONTAL_INPUT_SPEED = 1.0f;
	float modifierX = 1.0f;
	const float IN_AIR_MODIFIED_X = 0.25f;
	const float ON_GROUND_MODIFIED_X = 1.0f;
	const float ZIPLINE_OFFSET_END=25.0f;
};
