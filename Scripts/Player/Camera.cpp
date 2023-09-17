#include "precomp.h"
#include "Camera.h"



Camera::Camera()
= default;

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
#ifdef _DEBUG
	screen->Box(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), SCRWIDTH - 1, SCRHEIGHT - 1, 255 << 16);
#endif
}

void Camera::UpdatePosition(float deltaTime, float2 player_pos)
{

	//TODO  use delta time to smooth the camera movement
	const float2 newPos = (player_pos - float2{ SCRWIDTH / 2, SCRHEIGHT / 2 });

	//// Clamp position shorthand conditionals from Lynn


	pos.x = newPos.x < 0 ? 0 : newPos.x > maxPosX ? maxPosX : newPos.x;
	pos.y = newPos.y < 0 ? 0 : newPos.y > maxPosY ? maxPosY : newPos.y;

}

float2 Camera::GetPosition() const
{
	return pos;
}
//make sure this works
const float2& Camera::pGetPosition() const
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

bool Camera::OnScreen(float2 screenPos, const AABB& _a)
{
	AABB a = _a.At(screenPos);

	return OnScreen({ a.min.x,a.min.y }) ||
		OnScreen({ a.min.x,a.max.y }) ||
		OnScreen({ a.max.x,a.min.y }) ||
		OnScreen({ a.max.x,a.max.y });
}
