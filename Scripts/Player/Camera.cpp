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
	maxPosX = static_cast<float>(tileMap->GetWidth()) - resX - 1;
	maxPosY = static_cast<float>(tileMap->GetHeight()) - resY - 1;

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
	tileMap = tilemapSurface;
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

void Camera::CleanPreRenderSurface() const
{

	preRender->GetSurface()->Clear(0);
}

void Camera::RenderTilemaps() const
{

	const float2 screenPos = -pos;

	parallax->Render(preRender->GetSurface());
	tileMap->Draw(preRender->GetSurface(),
		static_cast<int>(screenPos.x), static_cast<int>(screenPos.y));

}

void Camera::UpdatePosition(float deltaTime, float2 playerPos, float leftOrRight)
{

	//apply camera scaling to the offset
	const float2 cameraOffset = playerPos -
		float2{ CAMERA_OFFSET.x * leftOrRight * currentCameraScale,
			CAMERA_OFFSET.y * currentCameraScale };
	const float2 halfScreen{ resX / 2, resY / 2 };
	float multiplier = invlerp(0, EASE_OUT_DISTANCE, 
		length((cameraOffset - halfScreen) - pos));
	const float step = clamp(deltaTime * (CAM_SPEED * CAM_SPEED_EDGE * multiplier), 
		0.0f, 1.0f);
	const float2 newPos = lerp(pos, (cameraOffset - halfScreen), step);

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
bool Camera::OnScreen(const Box& _a)
{
	const Box b = Box{ pos,pos + float2{resX,resY} };
	return AABB::BoxCollides(_a, b);
}

bool Camera::OnScreen(float2 worldPos, const Box& _a)
{
	const Box a = AABB::At(worldPos, _a);
	const Box b = Box{ pos,pos + float2{resX,resY} };
	return AABB::BoxCollides(a, b);

}
bool Camera::SmallerThanScreenComplete(float2 worldPos, const Box& _a)
{
	const Box a = AABB::At(worldPos, _a);

	return OnScreen(float2{ a.min.x,a.min.y }) &&
		OnScreen(float2{ a.min.x,a.max.y }) &&
		OnScreen(float2{ a.max.x,a.min.y }) &&
		OnScreen(float2{ a.max.x,a.max.y });
}

Surface* Camera::pGetPreRender()
{
	return preRender->GetSurface();
}
