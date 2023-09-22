#pragma once

class State
{
public:
	virtual ~State() = default;
	virtual void OnEnter() = 0;
	virtual void Update(Avatar& player, Input input, float deltaTime) = 0;
	virtual void OnExit() = 0;

};
