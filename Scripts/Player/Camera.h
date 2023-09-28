#pragma once


class Parallax;

class Camera
{
public:
	Camera();
	~Camera();
	void GetInput(float input);
	void Init(float2 screenPos, Sprite* tilemapSurface, Sprite* parallaxSurface);
	void RenderToScreen(Surface* screen) const;
	void CleanPreRenderSurface() const;
	void RenderTilemaps() const;
	void UpdatePosition(float deltaTime, float2 playerPos, float leftOrRight);
	static float2 GetPosition();
	void Update(float deltaTime);
	static bool OnScreen(float2 worldPos);
	static bool OnScreen(const Box& _a);
	static bool OnScreen(float2 screenPos, const Box& a);
	static bool SmallerThanScreenComplete(float2 worldPos, const Box& _a);
	Surface* pGetPreRender();
private:
	void SetCameraScale(float cameraScale);

	Parallax* parallax = nullptr;
	const float EASE_OUT_DISTANCE = 120.0f;
	inline static float2 pos = 0;
	Sprite* tilemap = nullptr;
	Sprite* preRender = nullptr;
	const float CAM_SPEED = 1.0f;
	const float CAM_SPEED_EDGE = 15.0f;
	const float DEFAULT_CAMERA_SCALE = 0.4f;
	//scaling camera
	const float2 CAMERA_OFFSET = { 150 ,-50 };
	float inputScaling = 0;
	const float INCREMENT_SCALE = .01f;
	const float ZOOMING_SPEED = 50.0f;
	const float MIN_SCALE = .4f;
	const float MAX_SCALE = .6f;
	float maxPosX = 0;
	float maxPosY = 0;
	inline static float resX{};
	inline static float resY{};
	float currentCameraScale = 0;
};
