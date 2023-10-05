﻿#pragma once

struct Timer;
class Observer;
class Parallax;

class Camera: public Observer , public Entity
{
public:

	Camera();
	~Camera() override;
	void SetInputScaling();
	void Init(float2 screenPos, Sprite* tilemapSurface, Sprite* parallaxSurface);
	//still behaves like an entity using render for scaling
	void Render(Surface* screen)override;
	void CleanPreRenderSurface() const;
	void RenderTilemaps() const;
	void UpdatePosition(float deltaTime, float2 playerPos, float leftOrRight);
	static float2 GetPosition();
	void Update(float deltaTime) override;
	static bool OnScreen(float2 worldPos);
	static bool OnScreen(const Box& _a);
	static bool OnScreen(float2 screenPos, const Box& a);
	static bool SmallerThanScreenCompleteCollision(float2 worldPos, const Box& _a);
	Surface* pGetPreRender();
	inline static float resX{};
	inline static float resY{};
	void Notify(int context, EVENT ev) override;
private:
	void SetCameraScale(float cameraScale);

public:

private:
	const float2 CAMERA_OFFSET = { 150.0f,-50.0f };

	Timer* t;
	const float DELAY_ZOOM = .5f;
	Parallax* parallax = nullptr;
	const float EASE_OUT_DISTANCE = 120.0f;
	inline static float2 pos = 0;
	Sprite* tileMap = nullptr;
	Sprite* preRender = nullptr;
	const float CAM_SPEED = 1.0f;
	const float CAM_SPEED_EDGE = 30.0f;
	const float DEFAULT_CAMERA_SCALE = 0.4f;
	//scaling camera
	float inputScaling = 0;
	float desiredCameraScaling;
	const float INCREMENT_SCALE = .05f;
	const float ZOOMING_SPEED = 50.0f;
	const float MIN_SCALE = .4f;
	const float MAX_SCALE = .6f;
	float maxPosX = 0;
	float maxPosY = 0;

	float currentCameraScale = 0;
};
