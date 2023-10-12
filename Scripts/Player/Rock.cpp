#include "precomp.h"
#include "Rock.h"



void Rock::Init(const float2& _pos, const float2& _dir) 
{
	pos = _pos;
	dir = _dir;
	col = Box{ -DISTANCE_TO_ENEMY, DISTANCE_TO_ENEMY };
	timer = new Timer();
}

Rock::~Rock()
{
	delete timer;
}

const float2& Rock::GetPosition() const
{
	return pos;
}

void Rock::Update(float deltaTime)
{
	pos += dir * SPEED * deltaTime;
	if (timer->elapsedF() > TIME_ALIVE)
		SetActive(false);
}


 const Box& Rock::GetBoxCollider() const
 {
	 return col;
}

bool Rock::GetActive() const
{
	return active;
}

void Rock::SetActive(bool val) 
{
	active = val;
	if (active)
		timer->reset();
}
