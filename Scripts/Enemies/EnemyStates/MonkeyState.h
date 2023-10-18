#pragma once

class Monkey;

class MonkeyState
{
public:
	virtual ~MonkeyState() = default;
	virtual void OnEnter() = 0;
	virtual MonkeyState* Update(Monkey* monkey, float deltaTime) = 0;
	virtual void OnExit() = 0;

protected:
	float t = 0;
};
