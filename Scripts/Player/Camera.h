#pragma once
#include "Scripts/Utilities/AABB.h"


class Camera
{
public:
	Camera();
	void Init(float2 screenPos, Sprite* tilemapSurface);
	void Render(Surface* screen);
	void UpdatePosition(float deltaTime, const float2 player_pos);
	float2 GetPosition()const;
private:
	float2 pos;
	AABB camBounds;
	Sprite* tilemap;
	const float CAM_SPEED = 50.0f;

	float maxPosX, maxPosY;
};
