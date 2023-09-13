#include "precomp.h"
#include "Tilemap.h"

#include <iostream>

#include "Scripts/Utilities/WorldLocalScreenTransf.h"

Tilemap::Tilemap() : widthX(0), heightY(0),
tileMap{},
tilePalette(nullptr),
halfTilemapX(0),
halfTilemapY(0)
{
}

Tilemap::~Tilemap()
{
	delete tilePalette;
	delete[] tileMap;
}

bool Tilemap::IsColliding(const float x, const float y) const
{
	const int tx = static_cast<int>(x / TILE_SIZE);
	const int ty = static_cast<int>(y / TILE_SIZE);
	const size_t index = tx + ty * widthX;
	if (tileMap[index] != 0)
		return true;
	return false;
}

//remade from https://github.com/Tycro-Games/AUSS/blob/master/src/Tilemap.cpp
bool Tilemap::IsCollidingBox(float2 _pos, AABB _a)
{
	//take the four corners of the box and check them

	const AABB a = _a.At(_pos);
	const float minX = a.min.x;
	const float minY = a.min.y;

	const float maxX = a.max.x;
	const float maxY = a.max.y;
	//check all the corners
	return IsColliding(minX, minY)
		&& IsColliding(minX, maxY)
		&& IsColliding(maxX, minY)
		&& IsColliding(maxX, maxY);

}

void Tilemap::ConvertCharToInt(const char* pch, uint& numberForm)
{
	uint moveToRight = 1;
	for (size_t i = 0; i < strlen(pch); i++)
	{
		numberForm = numberForm * moveToRight + pch[i] - '0';//conversion from char to int
		moveToRight = 10;
	}

}

void Tilemap::ExtractWidthHeight(const char* tilemapRaw)
{
	//widthX and heightY get
	char* tilemap = new char[strlen(tilemapRaw) + 1];
	strcpy(tilemap, tilemapRaw);

	char* getX = strstr(tilemap, "width=") + strlen("width=");
	char* getY = strstr(tilemap, "height=") + strlen("height=");
	const char* pX = strtok(getX, "\"");
	const char* pY = strtok(getY, "\"");

	ConvertCharToInt(pX, widthX);

	ConvertCharToInt(pY, heightY);
	tileMap = new uint[widthX * heightY];
	delete[] tilemap;
}

void Tilemap::loadCSVFile(const char* csvPath)
{
	//copy into a c style string
	char* tilemapRaw = new char[strlen(TextFileRead(csvPath).c_str()) + 1];
	strcpy(tilemapRaw, TextFileRead(csvPath).c_str());

	//print the whole file
	//cout << tilemapRaw << "\n";
	ExtractWidthHeight(tilemapRaw);

	//csv file
	//get to the start of the csv
	char* startOfCsv = strstr(tilemapRaw, "csv\">\n") + strlen("csv\">\n");

	//print the start of the csv
	//cout << startOfCsv << "\n";

	const char* pch = strtok(startOfCsv, ",");

	int index = 0;
	while (*pch != '<')//stops when it reaches the end of the csv
	{
		uint numberForm = 0;
		ConvertCharToInt(pch, numberForm);
		//makes it work with numbers with more than one digit

		tileMap[index++] = numberForm;
		pch = strtok(NULL, ",\n");
	}
	//cout << "\n";
	//change to values from file
	/*for (uint i = 0; i < heightY; i++)
	{
		for (uint j = 0; j < widthX; j++)
			cout << tileMap[j + i * widthX] << " ";
		cout << '\n';
	}*/
	delete[] tilemapRaw;

}

void Tilemap::RenderTile(Surface* surface,
	int screenX, int screenY, uint sourceX, uint sourceY)
{
	//the x and y for the left down corner of the tile
	const int maxScreenX = screenX + TILE_SIZE;
	const int maxScreenY = screenY + TILE_SIZE;
	//surface bounds
	const int minBoundaryX = 0;
	const int minBoundaryY = 0;
	const int maxBoundaryX = surface->width;
	const int maxBoundaryY = surface->height;
	//determine if tile is on surface
	if (maxScreenX >= minBoundaryX && maxScreenY >= minBoundaryY
		&& screenX <= maxBoundaryX && screenY <= maxBoundaryY)
	{
		//partial rendering of tiles
		const int minOffsetX = max(minBoundaryX, screenX);
		const int minOffsetY = max(minBoundaryY, screenY);

		const int maxOffsetX = min(maxBoundaryX, maxScreenX);
		const int maxOffsetY = min(maxBoundaryY, maxScreenY);

		//offsets for surface and source

		const uint2 offsetMin = { abs((minOffsetX - (screenX))),
			abs((minOffsetY - screenY)) };

		const uint2 offsetMax = { abs((maxOffsetX - maxScreenX)),
			abs((maxOffsetY - maxScreenY)) };

		screenX += offsetMin.x;
		screenY += offsetMin.y;

		sourceX += offsetMin.x;
		sourceY += offsetMin.y;

		const uint width = TILE_SIZE - offsetMin.x - offsetMax.x;
		const uint height = TILE_SIZE - offsetMin.y - offsetMax.y;


		uint* scr = surface->pixels
			+ screenX + screenY * surface->width;

		const uint* sou = tilePalette->pixels
			+ sourceX + sourceY * tilePalette->width;

		for (uint i = 0; i < height; i++)
		{
			for (uint j = 0; j < width; j++)
			{
				scr[j] = sou[j];
			}
			scr += surface->width;
			sou += tilePalette->width;
		}
	}
}



void Tilemap::Init(float2 screenPos, const char* sourceFile, const char* csvPath)
{

	tilePalette = new Surface(sourceFile);
	loadCSVFile(csvPath);


}
void Tilemap::DebugBox(Surface* screen) const
{
	for (uint i = 0; i < heightY; i++)
	{
		for (uint j = 0; j < widthX; j++)
		{
#ifdef _DEBUG
			uint index = tileMap[j + i * widthX];
			if (index)
				screen->Box(j * TILE_SIZE,
					i * TILE_SIZE,
					(j + 1) * TILE_SIZE,
					(i + 1) * TILE_SIZE, 255);
#endif
		}
	}
}
void Tilemap::Render(Surface* screen)
{
	for (int i = 0; i < heightY; i++)
	{
		for (int j = 0; j < widthX; j++)
		{
			uint index = tileMap[j + i * widthX];
			if (index)//index !=0
			{
				//so the index can start from 0

				index--;
				//get widthX and heightY position of the source
				const uint source_y = index / (tilePalette->width / TILE_SIZE);
				const uint source_x = index % (tilePalette->width / TILE_SIZE);
				RenderTile(screen,
					j * TILE_SIZE,
					i * TILE_SIZE,
					source_x * TILE_SIZE,
					source_y * TILE_SIZE);



			}
		}
	}
}



void Tilemap::Update(float deltaTime)
{

	//nothing to do
}



