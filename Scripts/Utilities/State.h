#pragma once

class Avatar;

class State
{
public:
	virtual ~State() = default;
	virtual void OnEnter(Avatar& p) = 0;
	virtual State* Update(Avatar& player, float deltaTime) = 0;
	virtual void OnExit() = 0;
protected:
	virtual void SetVariables(Avatar& p);
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
