#include "precomp.h"
#include "Parallax.h"

Parallax::Parallax(Sprite* _sprite, float2* cam)
	:
	sprite(_sprite), pCamPosition(cam)
{
	lastCamPosition = *pCamPosition;
	pos = -lastCamPosition;
}

void Parallax::Render(Surface* screen)
{
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void Parallax::Update(float deltaTime)
{
	const float2 dir = (-*pCamPosition + lastCamPosition);
	//prevent -nan(ind) by checking magnitude non zero
	if (sqrLength(dir) > 0) //more efficient than length by not doing sqrtf  
		normalize(dir);
	pos += dir * SPEED * deltaTime;
	lastCamPosition = *pCamPosition;
}
