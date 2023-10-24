#include "precomp.h"
#include "SavingLoading.h"
using json = nlohmann::json;

SavingLoading::~SavingLoading()
{
	delete[] saveName;
}

SavingLoading::SavingLoading(const char* name)
{
	SetName(name);
}

void SavingLoading::SetName(const char* name)
{
	delete[] saveName;
	saveName = new char[strlen(name) + 1];
	strcpy(saveName, name);
}

void SavingLoading::SaveData(uint& data) const
{
	json j;
	LoadJsonFile(j);

	j[saveName] = data;
	std::ofstream o(savePath);
	o << std::setw(4) << j << std::endl;
}

void SavingLoading::SaveData(float& data) const
{
	json j;
	LoadJsonFile(j);

	j[saveName] = data;
	std::ofstream o(savePath);
	o << std::setw(4) << j << std::endl;
}

void SavingLoading::SaveData(uint8_t& data) const
{
	json j;
	LoadJsonFile(j);

	j[saveName] = data;
	std::ofstream o(savePath);
	o << std::setw(4) << j << std::endl;
}

void SavingLoading::LoadJsonFile(json& j) const
{
	ifstream i(savePath);
	//read json
	i >> j;
}

void SavingLoading::LoadData(uint& outData) const
{
	json j;
	LoadJsonFile(j);
	outData = j[saveName];
}

void SavingLoading::LoadData(uint8_t& outData) const
{
	json j;
	ifstream i(savePath);
	//read json
	i >> j;
	outData = j[saveName];
}

void SavingLoading::LoadData(float& outData) const
{
	json j;
	ifstream i(savePath);
	//read json
	i >> j;
	if (j[saveName].is_number_float())
		outData = j[saveName];
}
