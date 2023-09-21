﻿#pragma once


class Parallax;

class Camera
{
public:
	Camera();
	~Camera();
	void GetInput(float input);
	void Init(float2 screenPos, Sprite* tilemapSurface, Sprite* parallaxSurface);
	void RenderToScreen(Surface* screen) const;
	void RenderTilemaps() const;
	void UpdatePosition(float deltaTime, float2 playerPos, const float2 leftOrRight);
	float2 GetPosition()const;
	void Update(float deltaTime);
	static bool OnScreen(float2 screenPos);
	static bool OnScreen(float2 screenPos, const Box& a);
	Surface* pGetPreRender();
private:
	void SetCameraScale(const float cameraScale);

	Parallax* parallax = nullptr;
	float2 pos = 0;
	Sprite* tilemap = nullptr;
	Sprite* preRender = nullptr;
	const float CAM_SPEED = 25.0f;
	const float DEFAULT_CAMERA_SCALE = 0.5f;
	//scaling camera
	float inputScaling = 0;
	const float INCREMENT_SCALE = .01f;
	const float ZOOMING_SPEED = 50.0f;
	const float MIN_SCALE = .4f;
	const float MAX_SCALE = .6f;
	float maxPosX = 0;
	float maxPosY = 0;
	float resX{};
	float resY{};
	float currentCameraScale = 0;
};
