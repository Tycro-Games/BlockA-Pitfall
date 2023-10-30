#pragma once

struct Timer;
class Observer;
class Parallax;

class Camera : public Observer, public Entity
{
public:
	Camera();
	~Camera() override;
	void LoadCheckPoint();
	void SetInputScaling();
	void Init(Sprite* tilemapSurface, Sprite* parallaxSurface);
	//still behaves like an entity using render for scaling
	void Render(Surface* screen) override;
	void CleanPreRenderSurface() const;
	void RenderTilemaps() const;
	void UpdatePosition(float deltaTime, const float2& playerPos, float leftOrRight) const;
	static float2 GetPosition();
	void Update(float deltaTime) override;
	static bool OnScreen(float2 worldPos);
	static bool OnScreen(const Box& _a);
	static bool OnScreen(const float2& screenPos, const Box& a);
	static bool SmallerThanScreenCompleteCollision(const float2& worldPos, const Box& _a);
	Surface* pGetPreRender() const;
	inline static float resX{};
	inline static float resY{};
	void Notify(int context, EVENT ev) override;
	void SetPosition(const float2& screenPos);

private:
	void SetCameraScale(float cameraScale);

	inline static float2 pos = 0;


	Parallax* parallax = nullptr;
	Sprite* tileMap = nullptr;
	Sprite* preRender = nullptr;
	Timer* t = nullptr;

	SavingLoading saveLoad;


	const float DELAY_ZOOM = .5f;
	const float EASE_OUT_DISTANCE_Y = 120.0f;
	const float EASE_OUT_DISTANCE_X = 350.0f;
	const float CAMERA_OFFSET_X = {150.0};
	const float CAMERA_OFFSET_Y = {-50.0f};

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
