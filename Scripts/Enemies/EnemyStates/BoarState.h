#pragma once
class BoarState
{
public:
	virtual ~BoarState() = default;
	virtual void OnEnter() = 0;
	virtual BoarState* Update(Boar* boar, float deltaTime) = 0;
	virtual void OnExit() = 0;
protected:
	float t = 0;

};