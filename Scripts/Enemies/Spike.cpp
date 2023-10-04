#include "precomp.h"
#include "Spike.h"

void Spike::Init(const float2& _position, Avatar* _avatar)
{
	position = _position;
	avatar = _avatar;
	subject = new Subject();
	col = Box{ position - DISTANCE_TO_PLAYER,position + DISTANCE_TO_PLAYER };
}

void Spike::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(col);
	if (!onScreen)
		return;
	if (length(avatar->GetCollisionChecker()->GetBoxColliderPos() - position) <= DISTANCE_TO_PLAYER)//hit event
	{
		subject->Notify(DAMAGE, PLAYER_HIT);
	}
}



Spike::~Spike()
{
	delete subject;
}

void Spike::Render(Surface* screen)
{
	if (!onScreen)return;
	x1 = static_cast<int>(col.min.x - Camera::GetPosition().x);
	x2 = static_cast<int>(col.max.x - Camera::GetPosition().x);

	y1 = static_cast<int>(col.min.y - Camera::GetPosition().y);
	y2 = static_cast<int>(col.max.y - Camera::GetPosition().y);
	screen->Box(x1, y1, x2, y2, ORANGE);
}
