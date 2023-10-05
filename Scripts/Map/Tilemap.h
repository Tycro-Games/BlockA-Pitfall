#pragma once


struct Box;
struct Circle;

//origin of the world {0 0}
class Tilemap
{
	
public:
	enum TilemapType
	{
		PARALLAX,
		BG,
		FLOOR,
		LADDERS,
		COUNT
	};
	Tilemap();
	~Tilemap();
	//collision
	bool IsColliding(float x, float y) const;
	bool IsColliding(float x, float y, float2& floorPos) const;
	bool IsCollidingBox(float2 pos, const Box& a) const;
	bool IsCollidingBoxComplete(float2 _pos, const Box& _a) const;
	bool IsCollidingBox(float2 _pos, const Box& _a, float2& floorPos);
	
	
	void Init(const char* sourceFile, const char* csvPath);
	void DebugBox(Surface* screen) const;
	void Render(Surface* screen);
	uint GetTileColumn(float2 pos) const
	{
		const int ty = static_cast<int>(pos.x / static_cast<float>(TILE_SIZE));
		return ty;
	}
	int GetWidth() const
	{
		return widthX * TILE_SIZE;
	}
	int GetHeight() const
	{
		return  heightY * TILE_SIZE;
	}
	static void ConvertCharToInt(const char* pch, uint& numberForm);

private:
	void ExtractWidthHeight(const char* csvRaw);
	void LoadCSVFile(const char* csvPath);
	//modified from my previous implementation https://github.com/Tycro-Games/AUSS/blob/master/src/Tilemap.cpp
	void RenderTile(Surface* surface, int screenX, int screenY, uint sourceX, uint sourceY);


	uint widthX;
	uint heightY;
	uint* tileMap;//number of tiles might need to be dynamic

	Surface* tilePalette;
	const int TILE_SIZE = 32;

};

