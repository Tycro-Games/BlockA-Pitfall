#pragma once

class SpawnNonTiles
{
public:

	void Init(const char* csvPath);
	size_t GetCount() const;
	float2 GetPosition(size_t index) const;
private:
	void LoadCSVFile(const char* csvPath);
	void ExtractPositions(const char* csvRaw);
	void ConvertCharTofloat(const char* pch, float& numberForm);
	float2 positions[50] = {};//should be made a vector;
	size_t index = 0;
};
