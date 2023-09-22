#pragma once
class MovingOnGroundState : State
{
	// Inherited via State
	void OnEnter() override;
	void SetVariables(Avatar& p, Input input, float deltaTime, float2& pos, float2& newPos,
	                  Tilemap*& floors, Camera*& cam, Box& floorCollider, Box& boxCollider, float2& velocity);
	void Update(Avatar& player, Input input, float deltaTime) override;
	void OnExit() override;
};

