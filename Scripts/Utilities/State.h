#pragma once

class State
{
public:
	virtual ~State() = default;
	virtual void OnEnter() = 0;
	virtual State* Update(Avatar& player, Input input, float deltaTime)=0;
	virtual void OnExit() = 0;
protected:
	void SetVariables(Avatar& p, float deltaTime, float2& pos, float2& newPos,
		Tilemap*& floors, Camera*& cam, Box& floorCollider, Box& boxCollider, float2& velocity);
};
