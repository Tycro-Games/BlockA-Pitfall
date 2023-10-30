#pragma once

class Parallax
{
public:
	Parallax(Sprite* sprite, float2* cam);
	void Render(Surface* screen) const;
	void Update(float deltaTime);

private:
	Sprite* sprite = nullptr;
	float2* pCamPosition = nullptr;
	float2 lastCamPosition = 0;
	float2 pos = 0;
	const float SPEED = 29.0f;
};
