#include "precomp.h"
#include "Camera.h"




Camera::Camera()
{
}

Camera::~Camera()
{
	delete parallax;
	delete preRender;
}

void Camera::GetInput(float input)
{
	inputScaling = input;

}

void Camera::SetCameraScale(const float cameraScale)
{

	currentCameraScale = clamp(cameraScale, MIN_SCALE, MAX_SCALE);

	resX = currentCameraScale * SCRWIDTH;
	resY = currentCameraScale * SCRHEIGHT;
	maxPosX = static_cast<float>(tilemap->GetWidth()) - resX - 1;
	maxPosY = static_cast<float>(tilemap->GetHeight()) - resY - 1;

	//we need a new surface for rendering
	delete preRender;
	Surface* s = new Surface(static_cast<int>(resX), static_cast<int>(resY));
	//clean it so the sprite optimization still draws it
	s->Clear(0xff000000);
	preRender = new Sprite(s, 1);
}

void Camera::Init(float2 screenPos, Sprite* tilemapSurface, Sprite* parallaxSurface)
{

	pos = screenPos;
	tilemap = tilemapSurface;
	currentCameraScale = DEFAULT_CAMERA_SCALE;
	SetCameraScale(DEFAULT_CAMERA_SCALE);
	parallax = new Parallax(parallaxSurface, &pos);





}

void Camera::RenderToScreen(Surface* screen) const
{
	preRender->DrawScaled(0, 0,
		SCRWIDTH, SCRHEIGHT,
		screen);
}

void Camera::RenderTilemaps() const
{

	const float2 screenPos = -pos;
	preRender->GetSurface()->Clear(0);

	parallax->Render(preRender->GetSurface());
	tilemap->Draw(preRender->GetSurface(),
		static_cast<int>(screenPos.x), static_cast<int>(screenPos.y));

}

void Camera::UpdatePosition(float deltaTime, float2 playerPos, float2 leftOrRight)
{
	//apply camera scaling to the offset
	const float2 cameraOffset = playerPos - leftOrRight * currentCameraScale;
	const float2 halfScreen{ resX / 2, resY / 2 };
	const float2 newPos = lerp(pos, (cameraOffset - halfScreen), deltaTime * CAM_SPEED);

	pos.x = newPos.x < 0 ? 0 : newPos.x > maxPosX ? maxPosX : newPos.x;
	pos.y = newPos.y < 0 ? 0 : newPos.y > maxPosY ? maxPosY : newPos.y;

	parallax->Update(deltaTime);
}

float2 Camera::GetPosition()
{
	return pos;

}


void Camera::Update(float deltaTime)
{
	if (inputScaling) {
		const float step = -inputScaling * INCREMENT_SCALE;
		SetCameraScale(lerp(currentCameraScale, step + currentCameraScale, deltaTime * ZOOMING_SPEED));
		inputScaling = 0;
	}
}

bool Camera::OnScreen(float2 worldPos)
{
	return worldPos.x >= pos.x
		&& worldPos.y >= pos.y &&
		worldPos.y < pos.y + resY
		&& worldPos.x < pos.x + resX;
}

bool Camera::OnScreenPartial(float2 worldPos, const Box& _a)
{
	const Box a = AABB::At(worldPos, _a);

	return OnScreen({ a.min.x,a.min.y }) ||
		OnScreen({ a.min.x,a.max.y }) ||
		OnScreen({ a.max.x,a.min.y }) ||
		OnScreen({ a.max.x,a.max.y });
}
bool Camera::OnScreenAll(float2 worldPos, const Box& _a)
{
	const Box a = AABB::At(worldPos, _a);

	return OnScreen({ a.min.x,a.min.y }) &&
		OnScreen({ a.min.x,a.max.y }) &&
		OnScreen({ a.max.x,a.min.y }) &&
		OnScreen({ a.max.x,a.max.y });
}

Surface* Camera::pGetPreRender()
{
	return preRender->GetSurface();
}
