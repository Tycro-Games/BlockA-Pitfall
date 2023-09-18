#pragma once
#include "Scripts/Utilities/AABB.h"


class Camera
{
public:
	Camera();
	void Init(float2 screenPos, Sprite* tilemapSurface);
	void Render(Surface* screen) const;
	void UpdatePosition(float deltaTime, const float2 player_pos);
	float2 GetPosition()const;
	const float2& pGetPosition()const;
	static bool OnScreen(float2 screenPos);
	static bool OnScreen(float2 screenPos, const Box& a);
private:
	float2 pos{};
	AABB camBounds;
	Sprite* tilemap{};
	const float CAM_SPEED = 25.0f;
	
	float maxPosX{}, maxPosY{};
};
