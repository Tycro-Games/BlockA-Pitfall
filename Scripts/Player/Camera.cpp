#include "precomp.h"
#include "Camera.h"

#include <iostream>


Camera::Camera()
= default;

void Camera::Init(float2 screenPos, Sprite* tilemapSurface)
{
	pos = screenPos;
	tilemap = tilemapSurface;
	camBounds = AABB{ {0,0},{SCRWIDTH,SCRHEIGHT} };

	maxPosX = tilemap->GetWidth() - SCRWIDTH - 1;
	maxPosY = tilemap->GetHeight() - SCRHEIGHT - 1;
}

void Camera::Render(Surface* screen)
{
	const float2 _worldPos = -pos;
	cout << pos;
	tilemap->Draw(screen, static_cast<int>(_worldPos.x), static_cast<int>(_worldPos.y));
#ifdef _DEBUG
	screen->Box(_worldPos.x, _worldPos.y, SCRWIDTH - 1, SCRHEIGHT - 1, 255 << 16);
#endif
}

bool Camera::UpdatePosition(float deltaTime, float2 player_pos)
{
	bool updatePos = true;
	const float2 newPos = pos + (player_pos - float2{ SCRWIDTH / 2,SCRHEIGHT / 2 });

	//// Clamp position //from lynn
	if (newPos.x < 0 || newPos.x > maxPosX ||
		newPos.y < 0 || newPos.y > maxPosY)
	{

		updatePos = false;
	}
	pos.x = (newPos.x <= 0) ? 0 : (newPos.x >= maxPosX) ? maxPosX : newPos.x;
	pos.y = (newPos.y <= 0) ? 0 : (newPos.y >= maxPosY) ? maxPosY : newPos.y;

	return  updatePos;
}

float2 Camera::GetPosition() const
{
	return pos;
}
