#include "precomp.h"
#include "NonTileMap.h"



void SpawnNonTiles::Init(const char* csvPath)
{
	LoadCSVFile(csvPath);
}

size_t SpawnNonTiles::GetCount() const
{
	return index + 1;
}

float2 SpawnNonTiles::GetPosition(size_t index) const
{
	return positions[index];
}

void SpawnNonTiles::LoadCSVFile(const char* csvPath)
{

	//copy into a c style string
	char* tilemapRaw = new char[strlen(TextFileRead(csvPath).c_str()) + 1];
	strcpy(tilemapRaw, TextFileRead(csvPath).c_str());


	ExtractPositions(tilemapRaw);
	delete[] tilemapRaw;

}
void SpawnNonTiles::ExtractPositions(const char* csvRaw)
{
	char* tilemap = new char[strlen(csvRaw) + 1];
	strcpy(tilemap, csvRaw);
	const uint INITIAL_OFFSET = 340;
	const uint NEXT_POSITION = 63;
	uint offsetIndex = INITIAL_OFFSET;//first position
	while (offsetIndex < strlen(tilemap)) {
		char* stringToEdit = new char[strlen(tilemap + offsetIndex) + 1];
		strcpy(stringToEdit, tilemap + offsetIndex);

		char* getX = strstr(stringToEdit, "x=");
		if (getX == nullptr) {//check for end
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
		positions[index++] = float2{ x,y };
		cout << x << " " << y << '\n';
		offsetIndex += NEXT_POSITION;
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
		if (pch[i] == '.') {//we are at the decimals
			decimals = true;
			continue;
		}
		if (!decimals) {
			numberForm = numberForm * moveToRightInt + pch[i] - '0';//conversion from char to int
			moveToRightInt = 10;
		}
		else
		{
			numberForm = numberForm + (pch[i] - '0') / decimalsToRight;//conversion from char to int
			decimalsToRight *= 10.0f;
		}

	}

}