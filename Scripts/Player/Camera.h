#pragma once


class Parallax;

class Camera
{
public:
	Camera();
	~Camera();
	void SetCameraScale(const float cameraScale);
	void Init(float2 screenPos, Sprite* tilemapSurface, Sprite* parallaxSurface);
	void RenderToScreen(Surface* screen) const;
	void Render(Surface* screen) const;
	void UpdatePosition(float deltaTime, float2 playerPos, const float2 leftOrRight);
	float2 GetPosition()const;
	static bool OnScreen(float2 screenPos);
	static bool OnScreen(float2 screenPos, const Box& a);
	Surface* pGetPreRender();
private:
	Parallax* parallax = nullptr;
	float2 pos = 0;
	Sprite* tilemap = nullptr;
	Sprite* preRender = nullptr;
	const float CAM_SPEED = 25.0f;
	const float DEFAULT_CAMERA_SCALE = .5f;
	//scaling camera
	float maxPosX = 0;
	float maxPosY = 0;
	float resX;
	float resY;
	float currentCameraScale=0;
};
