#include "precomp.h"
#include "Spike.h"

void Spike::Init(const float2& _position, Avatar& _avatar)
{
	position = _position;
	avatar = &_avatar;
	col = Box{position - DISTANCE_TO_PLAYER, position + DISTANCE_TO_PLAYER};
	SetDamage(DAMAGE);
}


void Spike::Update(float deltaTime)
{
	deltaTime;
	onScreen = Camera::OnScreen(col);
	if (!onScreen)
		return;
	TryToHitPlayer(DISTANCE_TO_PLAYER);
}


Spike::~Spike()
{
}


void Spike::Render(Surface* screen)
{
	if (!onScreen)return;
	GetDrawCoordinates();
	screen->Box(x1, y1, x2, y2, ORANGE);
}

float Spike::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}
