#include "precomp.h"
#include "NonTileMap.h"


void SpawnNonTiles::Init(const char* csvPath, bool half)
{
	LoadCSVFile(csvPath);
	if (half)
	{
		if (index % 2 != 0)
			cout << "non even number of positions!'\n";
		index /= 2;
	}
}

uint SpawnNonTiles::GetCount() const
{
	return index;
}

float2 SpawnNonTiles::GetPosition(size_t _index) const
{
	return positions[_index];
}

void SpawnNonTiles::LoadCSVFile(const char* csvPath)
{
	//copy into a c style string
	auto tilemapRaw = new char[strlen(TextFileRead(csvPath).c_str()) + 1];
	strcpy(tilemapRaw, TextFileRead(csvPath).c_str());


	ExtractPositions(tilemapRaw);
	delete[] tilemapRaw;
}

size_t SpawnNonTiles::GetNextXIndex(char* tilemap)
{
	const char* firstX = strstr(tilemap, "x=");
	return static_cast<size_t>(firstX - tilemap);
}

void SpawnNonTiles::ExtractPositions(const char* csvRaw)
{
	auto tilemap = new char[strlen(csvRaw) + 1];
	strcpy(tilemap, csvRaw);
	//this post showed how to use pointer substraction https://stackoverflow.com/questions/7500892/get-index-of-substring
	const size_t INITIAL_OFFSET = GetNextXIndex(tilemap);

	size_t offsetIndex = INITIAL_OFFSET; //first position
	while (offsetIndex < strlen(tilemap))
	{
		auto stringToEdit = new char[strlen(tilemap + offsetIndex) + 1];
		strcpy(stringToEdit, tilemap + offsetIndex);

		char* getX = strstr(stringToEdit, "x=");
		if (getX == nullptr)
		{
			//check for end
			delete[] stringToEdit;
			break;
		}
		getX += strlen("x=");
		char* getY = strstr(stringToEdit, "y=") + strlen("y=");

		const char* pX = strtok(getX, "\"");
		const char* pY = strtok(getY, "\"");

		float x = 0;
		float y = 0;
		ConvertCharTofloat(pX, x);

		ConvertCharTofloat(pY, y);
		positions[index++] = float2{x, y};
		//so it finds the next x=
		const size_t NEXT_POSITION = GetNextXIndex(tilemap + offsetIndex + 1);
		offsetIndex += NEXT_POSITION + 1;
		delete[] stringToEdit;
	}

	delete[] tilemap;
}

void SpawnNonTiles::ConvertCharTofloat(const char* pch, float& numberForm)
{
	uint moveToRightInt = 1;
	float decimalsToRight = 10.0f;
	bool decimals = false;
	for (size_t i = 0; i < strlen(pch); i++)
	{
		if (pch[i] == '.')
		{
			//we are at the decimals
			decimals = true;
			continue;
		}
		if (!decimals)
		{
			numberForm = numberForm * moveToRightInt + pch[i] - '0'; //conversion from char to int
			moveToRightInt = 10;
		}
		else
		{
			numberForm = numberForm + (pch[i] - '0') / decimalsToRight; //conversion from char to int
			decimalsToRight *= 10.0f;
		}
	}
}
