#include "precomp.h"
#include "Tilemap.h"

#include <iostream>

#include "Scripts/Utilities/MathLibrary.h"
#include "Scripts/Utilities/WorldLocalScreenTransf.h"

Tilemap::Tilemap() : worldPos(0), dir(), originalPos(), offset(), minBounds(), maxBounds(), widthX(0), heightY(0),
tileMap{},
tilePalette(nullptr),
halfTilemapX(0),
halfTilemapY(0)
{
}

Tilemap::~Tilemap()
{
	delete tilePalette;
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
	tileMap = new TileInfo[widthX * heightY];
	delete[]tilemap;
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

		tileMap[index++].index = numberForm;
		pch = strtok(NULL, ",\n");
	}
	//cout << "\n";
	//change to values from file
	/*for (uint i = 0; i < heightY; i++)
	{
		for (uint j = 0; j < widthX; j++)
			cout << tileMap[j + i * widthX].index << " ";
		cout << '\n';
	}*/
	delete[] tilemapRaw;
}

void Tilemap::RenderTile(Surface* screen,
	int screenX, int screenY, uint sourceX, uint sourceY)
{
	//the x and y for the left down corner of the tile
	const int maxScreenX = screenX + TILE_SIZE;
	const int maxScreenY = screenY + TILE_SIZE;
	//screen bounds
	const int minBoundaryX = 0;
	const int minBoundaryY = 0;
	const int maxBoundaryX = screen->width;
	const int maxBoundaryY = screen->height;
	//determine if tile is on screen
	if (maxScreenX >= minBoundaryX && maxScreenY >= minBoundaryY
		&& screenX <= maxBoundaryX && screenY <= maxBoundaryY)
	{
		//partial rendering of tiles
		const int minOffsetX =max(minBoundaryX, screenX);
		const int minOffsetY = max(minBoundaryY, screenY);

		const int maxOffsetX = min(maxBoundaryX, maxScreenX);
		const int maxOffsetY = min(maxBoundaryY, maxScreenY);

		//offsets for screen and source

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


		uint* scr = screen->pixels
			+ screenX + screenY * screen->width;

		const uint* sou = tilePalette->pixels
			+ sourceX + sourceY * tilePalette->width;

		for (uint i = 0; i < height; i++)
		{
			for (uint j = 0; j < width; j++)
			{
				scr[j] = sou[j];
			}
			scr += screen->width;
			sou += tilePalette->width;
		}
	}
}

void Tilemap::Init(float2 screenPos, const char* sourceFile, const char* csvPath)
{
	worldPos = WorldLocalScreenTransf::ConvertScreenToWorldSpace(screenPos);

	tilePalette = new Surface(sourceFile);
	loadCSVFile(csvPath);
	//to start at the bottom left part
	offset = {
		0 ,
	 static_cast<float>(TILE_SIZE * heightY) };

	originalPos = worldPos + offset;

}

void Tilemap::Render(Surface* screen)
{


	const float2 screenPos = WorldLocalScreenTransf::ConvertWorldSpaceToScreen(worldPos) - offset;
	for (int i = 0; i < heightY; i++)
	{
		for (int j = 0; j < widthX; j++)
		{
			uint index = tileMap[j + i * widthX].index;
			if (index)//index !=0
			{
				//so the index can start from 0

				index--;
				//get widthX and heightY position of the source
				const uint source_y = index / (tilePalette->width / TILE_SIZE);
				const uint source_x = index % (tilePalette->width / TILE_SIZE);
				RenderTile(screen,
					j * TILE_SIZE + static_cast<int>(screenPos.x),
					i * TILE_SIZE + static_cast<int>(screenPos.y),
					source_x * TILE_SIZE,
					source_y * TILE_SIZE);
			}
		}
	}
}

void Tilemap::ClampMap(float2& newPosition)
{
	const float boundX = TILE_SIZE * widthX - SCRWIDTH;
	const float boundY = TILE_SIZE * heightY - SCRHEIGHT;
	newPosition.x = clamp(newPosition.x, originalPos.x - boundX,
		originalPos.x);

	newPosition.y = clamp(newPosition.y, originalPos.y - boundY,
		originalPos.y);
}

void Tilemap::Update(float deltaTime)
{
	//movement
	float2 newPosition = worldPos + dir * deltaTime * speed;

	ClampMap(newPosition);

	movedLastFrame = static_cast<int>(newPosition.x) == static_cast<int>(worldPos.x) &&
		static_cast<int>(newPosition.y) == static_cast<int>(worldPos.y);

	
	worldPos = newPosition;

	dir = 0;//used input
}

void Tilemap::Move(int2 input)
{
	this->dir = input;
}

bool Tilemap::Moved() const
{
	return movedLastFrame;

}
