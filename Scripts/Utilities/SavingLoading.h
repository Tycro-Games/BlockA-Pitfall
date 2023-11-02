#pragma once

class SavingLoading
{
public:
	~SavingLoading();
	SavingLoading(const char* name);
	void SetName(const char* name);
	void EntryPosition(const float2& position);
	void SaveData(uint& data) const;
	void SaveData(int& data) const;
	void SaveData(float& data) const;
	void SaveData(uint8_t& data) const;
	void LoadData(uint& outData) const;
	void LoadData(int& outData) const;
	void LoadData(uint8_t& outData) const;
	void LoadData(float& outData) const;
	void ResetAllData() const;

private:
	void LoadJsonFile(nlohmann::json& j) const;

	const char* savePath = "assets/save.json";
	char* saveName = nullptr;
};
