#pragma once

class Avatar;

class State
{
public:
	virtual ~State() = default;
	virtual void OnEnter(Avatar& p) = 0;
	virtual State* Update(float deltaTime) = 0;
	virtual void OnExit() = 0;
protected:
	virtual void SetVariables(Avatar& p) = 0;

};
