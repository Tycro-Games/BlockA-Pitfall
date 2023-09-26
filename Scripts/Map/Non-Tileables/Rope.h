﻿#pragma once

class Rope 
{
public:
	Rope();
	~Rope() ;

	void Render(Surface* screen) ;
	void Update(float deltaTime);
	void Init(float2 _fixedPoint);
	bool GetOnScreen() const;
	float2 GetMovingPartAtTime(float timeElapsed);
	float2 GetMovingPart() const;


private:
	float2 fixedPoint = 0;
	float2 movingPoint = 0;
	const float len = 200.0f;
	const float frq = .8f;
	const float amp = 1.0f;
	const int halfWidth = 3;
	Timer* t;
	Box coll;
	bool onScreen = false;

};
