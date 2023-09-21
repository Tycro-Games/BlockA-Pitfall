#include "precomp.h"
#include "Camera.h"




Camera::Camera() : pos()
{
}

Camera::~Camera()
{
	delete parallax;
	delete preRender;
}

void Camera::SetCameraScale(const float cameraScale)
{
	currentCameraScale = cameraScale;
	resX = currentCameraScale * SCRWIDTH;
	resY = currentCameraScale * SCRHEIGHT;
	maxPosX = static_cast<float>(tilemap->GetWidth()) - resX - 1;
	maxPosY = static_cast<float>(tilemap->GetHeight()) - resY - 1;
}

void Camera::Init(float2 screenPos, Sprite* tilemapSurface, Sprite* parallaxSurface)
{

	pos = screenPos;
	tilemap = tilemapSurface;

	SetCameraScale(DEFAULT_CAMERA_SCALE);


	Surface* s = new Surface(static_cast<int>(resX), static_cast<int>(resY));
	s->Clear(0xff000000);
	parallax = new Parallax(parallaxSurface, &pos);
	preRender = new Sprite(s, 1);


}

void Camera::RenderToScreen(Surface* screen) const
{
	preRender->DrawScaled(0, 0, SCRWIDTH, SCRHEIGHT, screen);
	//preRender->Draw(screen, 0, 0);
}

void Camera::Render(Surface* screen) const
{

	const float2 screenPos = -(pos);//-float2{ SCRWIDTH / 2, SCRHEIGHT / 2 };
	preRender->GetSurface()->Clear(0);

	parallax->Render(preRender->GetSurface());
	tilemap->Draw(preRender->GetSurface(), screenPos.x, screenPos.y);




}

void Camera::UpdatePosition(float deltaTime, float2 playerPos, float2 leftOrRight)
{
	//apply camera scaling to the offset
	const float2 cameraOffset = playerPos - leftOrRight*currentCameraScale;
	const float2 newPos = lerp(pos, (cameraOffset - float2{ resX / 2, resY / 2 }), deltaTime* CAM_SPEED);

	pos.x = newPos.x < 0 ? 0 : newPos.x > maxPosX ? maxPosX : newPos.x;
	pos.y = newPos.y < 0 ? 0 : newPos.y > maxPosY ? maxPosY : newPos.y;
	parallax->Update(deltaTime);
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
	const Box a = AABB::At(screenPos, _a);

	return OnScreen({ a.min.x,a.min.y }) ||
		OnScreen({ a.min.x,a.max.y }) ||
		OnScreen({ a.max.x,a.min.y }) ||
		OnScreen({ a.max.x,a.max.y });
}

Surface* Camera::pGetPreRender()
{
	return preRender->GetSurface();
}
