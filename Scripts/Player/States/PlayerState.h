#pragma once

class Avatar;

class PlayerState
{
public:
	virtual ~PlayerState() = default;
	virtual void OnEnter(Avatar& p) = 0;
	virtual PlayerState* Update(float deltaTime) = 0;
	virtual void OnExit() = 0;
protected:
	Avatar* p = nullptr;

};
