#pragma once

class SavingLoading
{
public:
	~SavingLoading();
	SavingLoading(const char* name);
	void SetName(const char* name);
	void SaveData(uint& data) const;
	void SaveData(float& data) const;
	void SaveData(uint8_t& data) const;
	void LoadJsonFile(nlohmann::json& j) const;
	void LoadData(uint& outData) const;
	void LoadData(uint8_t& outData) const;
	void LoadData(float& outData) const;

private:
	const char* savePath = "assets/Saves/save.json";
	char* saveName = nullptr;
};
