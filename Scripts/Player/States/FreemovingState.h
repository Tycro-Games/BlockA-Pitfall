#pragma once

class FreemovingState final : public PlayerState
{
public:
	void OnEnter(Avatar& p) override;
	void AddJumpForce(const CollisionChecker* col, const Box* jumpCollider) const;
	void ClampHorizontalMovement(int signX) const;
	int SignOfHorizontalMovement() const;
	bool CheckZipRope(const CollisionChecker* col, const Box* floorCollider, const Box* boxCollider,
	                  PlayerState*& state);
	void MoveOnFloor(float deltaTime, const CollisionChecker* col, const Box* floorCollider, const Box* boxCollider);
	bool UpdateVelocity(float deltaTime) const;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;

private:
	//simmilar to the one in the climbing state
	PlayerState* ToTheLadder(float deltaTime);

	//for smooth ladder
	float currentTime = 0;
	float totalTimeToLadder = 0.1f;
	float2 originalPlayerPos = 0;
	float ladderPositionX = -1;
	const float CLIMB_DELAY = 0.5f;
	const float JUMP_FORCE = 2.2f;
	const float SMALL_JUMP_FORCE = 1.7f;
	const float GRAVITY = 9.8f;
	const float HORIZONTAL_GRAVITY = 12.0f;
	const float MAX_HORIZONTAL_SPEED = 3.0f;
	const float MAX_HORIZONTAL_INPUT_SPEED = 1.0f;
	float modifierX = 1.0f;
	const float IN_AIR_MODIFIED_X = 0.25f;
	const float ON_GROUND_MODIFIED_X = 1.0f;
};
