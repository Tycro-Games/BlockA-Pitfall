#pragma once
class ClimbingState : public State
{
public:

	// Inherited via State
	void OnEnter(Avatar& p) override;
	State* Update( float deltaTime) override;
	void OnExit() override;
protected:
	void SetVariables(Avatar& p) override;
private:
	const float CLIMBING_JUMP_FORCE = 2.5f;
	Timer* climbTimer = nullptr;
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

