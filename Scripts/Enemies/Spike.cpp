#include "precomp.h"
#include "Spike.h"

void Spike::Init(const float2& _position, Avatar* _avatar)
{
	position = _position;
	avatar = _avatar;
	subject = new Subject();
}

void Spike::Update(float deltaTime)
{
	if (length(avatar->GetCollisionChecker()->GetBoxColliderPos() - position) <= DISTANCE_TO_PLAYER)//hit event
	{
		subject->Notify(DAMAGE, PLAYER_HIT);
	}
}



Spike::~Spike()
{
	delete subject;
}
