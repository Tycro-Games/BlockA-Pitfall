﻿#pragma once

class SpawnNonTiles
{
public:
	enum NonTileType
	{
		ROPE,
		ZIPLINE,
		SPIKES,
		BOARS,
		MONKEYS,
		ELASTIC_PLANTS,
		COINS,
		CHECKPOINTS,
		COUNT
	};

	void Init(const char* csvPath, bool half = false);
	uint GetCount() const;
	float2 GetPosition(size_t index) const;

private:
	void LoadCSVFile(const char* csvPath);
	size_t GetNextXIndex(char* tilemap);
	void ExtractPositions(const char* csvRaw);
	void ConvertCharTofloat(const char* pch, float& numberForm);
	float2 positions[100] = {}; //should be made a vector;
	uint index = 0;
};
