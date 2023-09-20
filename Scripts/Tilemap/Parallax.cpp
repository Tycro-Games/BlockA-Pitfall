#include "precomp.h"
#include "Parallax.h"

Parallax::Parallax(Sprite* _sprite, float2* cam)
	:
	sprite(_sprite), pCamPosition(cam)
{
	lastCamPosition = *pCamPosition;
	pos = -lastCamPosition ;
}

void Parallax::Render(Surface* screen)
{


	sprite->Draw(screen, pos.x, pos.y);
}

void Parallax::Update(float deltaTime)
{
	pos += (-*pCamPosition + lastCamPosition) * SPEED * deltaTime;
	lastCamPosition = *pCamPosition;
	cout << pos;
}
