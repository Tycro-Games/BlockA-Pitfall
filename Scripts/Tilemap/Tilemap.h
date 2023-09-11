#pragma once

struct TileInfo
{
	uint index;
};
class Tilemap
{

public:
	Tilemap();
	~Tilemap();
	void ConvertCharToInt(const char* pch, uint& numberForm);
	void ExtractWidthHeight(const char* tilemapRaw);
	void loadCSVFile(const char* csvPath);
	//modified from my previous implementation https://github.com/Tycro-Games/AUSS/blob/master/src/Tilemap.cpp
	void RenderTile(Surface* screen, int screenX, int screenY, uint sourceX, uint sourceY);

	void Init(float2 screenPos, const char* sourceFile, const char* csvPath);
	void Render(Surface* screen);
	void ClampMap(float2& newPosition);
	void Update(float deltaTime);
	void Move(int2 input);
	bool Moved() const;
private:
	float2 worldPos, dir;
	float2 originalPos;
	float2 offset;
	float2 minBounds, maxBounds;
	uint widthX, heightY;
	bool movedLastFrame = false;
	TileInfo* tileMap;//number of tiles might need to be dynamic

	Surface* tilePalette;
	const int TILE_SIZE = 32;
	const float speed = 1000;
	int halfTilemapX, halfTilemapY;
};

