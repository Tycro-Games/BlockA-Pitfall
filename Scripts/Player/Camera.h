#pragma once


struct Box;

class Camera
{
public:
	Camera();
	void Init(float2 screenPos, Sprite* tilemapSurface);
	void Render(Surface* screen) const;
	void UpdatePosition(float deltaTime,  float2 player_pos);
	float2 GetPosition()const;
	static bool OnScreen(float2 screenPos);
	static bool OnScreen(float2 screenPos, const Box& a);
private:
	float2 pos;
	Sprite* tilemap;
	const float CAM_SPEED = 25.0f;
	float maxPosX, maxPosY;
};
