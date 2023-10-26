#include "precomp.h"
#include "Spike.h"

void Spike::Init(const float2& _position, Avatar& _avatar)
{
	position = _position;
	avatar = &_avatar;
	col = Box{position - DISTANCE_TO_PLAYER, position + DISTANCE_TO_PLAYER};
	SetDamage(-DAMAGE);
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
	delete sprite;
	sprite = nullptr;
}

Spike::Spike()
{
	sprite = new Sprite(new Surface("assets/Spike.png"), 1);
}


void Spike::Render(Surface* screen)
{
	if (!onScreen)return;
	GetDrawCoordinates();
#ifdef _DEBUG
	screen->Box(x1, y1, x2, y2, ORANGE);
#endif
	sprite->DrawScaled(x1, y1, SIZE_X, SIZE_Y, screen);
}

float Spike::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}
