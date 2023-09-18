#pragma once
#include "Scripts/Utilities/AABB.h"



//origin of the world {0 0}
class Tilemap
{

public:
	Tilemap();
	~Tilemap();
	bool IsColliding(float x, float y) const;
	bool IsColliding(float x, float y, float2& floorPos) const;
	bool OnFloor(const Circle& c, float2& floorPos) const;
	bool IsCollidingBox(float2 pos, const Box& a) const;
	bool IsCollidingBox(float2 _pos, const Box& _a, float2& floorPos);
	bool IsCollidingCircle(float2 _pos, const Circle& _a, float2& floorPos) const;
	void ConvertCharToInt(const char* pch, uint& numberForm);
	void ExtractWidthHeight(const char* tilemapRaw);
	void loadCSVFile(const char* csvPath);
	//modified from my previous implementation https://github.com/Tycro-Games/AUSS/blob/master/src/Tilemap.cpp
	void RenderTile(Surface* surface, int screenX, int screenY, uint sourceX, uint sourceY);
	void Init(const char* sourceFile, const char* csvPath);
	void DebugBox(Surface* screen) const;
	void Render(Surface* screen);
	void Update(float deltaTime);
	int GetWidth() const
	{
		return widthX * TILE_SIZE;
	}
	int GetHeight() const
	{
		return  heightY * TILE_SIZE;
	}
private:


	uint widthX, heightY;
	uint* tileMap;//number of tiles might need to be dynamic

	Surface* tilePalette;
	const int TILE_SIZE = 32;
	const float speed = 1000;
	int halfTilemapX, halfTilemapY;

	//Transform
};

