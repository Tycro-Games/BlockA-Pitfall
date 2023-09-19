#include "precomp.h"
#include "Camera.h"

#include <iostream>

#include "Scripts/Utilities/AABB.h"


Camera::Camera(): pos(), tilemap(nullptr), maxPosX(0), maxPosY(0)
{
}

Camera::~Camera()
{

}

void Camera::Init(float2 screenPos, Sprite* tilemapSurface)
{

	pos = screenPos;

	tilemap = tilemapSurface;

	maxPosX = static_cast<float>(tilemap->GetWidth() - SCRWIDTH - 1);
	maxPosY = static_cast<float>(tilemap->GetHeight() - SCRHEIGHT - 1);
}

void Camera::Render(Surface* screen) const
{
	const float2 screenPos = -pos;

	tilemap->Draw(screen,
		static_cast<int>(screenPos.x),
		static_cast<int>(screenPos.y));

	/*TODO add camera zooming
	 *Sprite* preRender = new Sprite(new Surface(SCRWIDTH, SCRHEIGHT), 1);
	tilemap->DrawScaled(0, 0, SCRWIDTH/4, SCRHEIGHT/4, preRender->GetSurface());
	preRender->Draw(screen,
		static_cast<int>(screenPos.x),
		static_cast<int>(screenPos.y));*/
	screen->Box(static_cast<int>(1), static_cast<int>(1), SCRWIDTH - 1, SCRHEIGHT - 1, 255 << 16);

#ifdef _DEBUG
	screen->Box(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), SCRWIDTH - 1, SCRHEIGHT - 1, 255 << 16);
#endif
}

void Camera::UpdatePosition(float deltaTime, float2 player_pos)
{

	const float2 newPos = lerp(pos,(player_pos - float2{ SCRWIDTH / 2, SCRHEIGHT / 2 }),deltaTime*CAM_SPEED);
	
	//// Clamp position shorthand conditionals from Lynn


	pos.x = newPos.x < 0 ? 0 : newPos.x > maxPosX ? maxPosX : newPos.x;
	pos.y = newPos.y < 0 ? 0 : newPos.y > maxPosY ? maxPosY : newPos.y;

}

float2 Camera::GetPosition() const
{
	return pos;
}

bool Camera::OnScreen(float2 screenPos)
{
	return screenPos.x >= 0
		&& screenPos.y >= 0 &&
		screenPos.y < SCRHEIGHT
		&& screenPos.x < SCRWIDTH;
}

bool Camera::OnScreen(float2 screenPos, const Box& _a)
{
	const Box a = AABB::At(screenPos,_a);

	return OnScreen({ a.min.x,a.min.y }) ||
		OnScreen({ a.min.x,a.max.y }) ||
		OnScreen({ a.max.x,a.min.y }) ||
		OnScreen({ a.max.x,a.max.y });
}
