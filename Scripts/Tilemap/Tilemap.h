#pragma once
constexpr size_t TILEMAP_LEVEL1 = 600;

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
	void Init(const char* sourceFile, const char* csvPath);
	void Render(Surface* screen);
	void Update(float deltaTime);
	void Move(int2 input);

private:
	float2 worldPos, dir;
	uint widthX, heightY;
	TileInfo tileMap[TILEMAP_LEVEL1];//number of tiles might need to be dynamic

	Surface* tilePalette;
	const uint TILE_SIZE = 32;

};
