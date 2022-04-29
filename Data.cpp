#include "Data.h"
#include "Location.h"
#include "Inventory.h"
#include "Character.h"

bool Data::canSaveData = false;

int Data::GetEnvironment(int index)
{
	if (Data::EnvironmentsSequence.size() > index)
		return *next(Data::EnvironmentsSequence.begin(), index);
	else
		throw("There is no such index!");
}

void Data::ReloadPossibilityDataSave()
{
	fstream fs;
	fs.open("Saved data/CanReloadData.txt", fstream::in);
	string str;
	getline(fs, str);
	istringstream(str) >> canSaveData;
	fs.close();
}

void Data::ChangePossibilityDataSave()
{
	if (!CanSaveData())
	{
		Data::AvailDataReloading();
		fstream fs;
		fs.open("Saved data/CanReloadData.txt", fstream::out);
		if (fs.is_open())
			fs << canSaveData;
		else
			cout << "File can't open";
		fs.close();
	}
}

void Data::ReloadAllStaticData()
{
	ReloadPossibilityDataSave();
	if (CanSaveData())
	{
		Location location;
		GeneralTime time;
		Character character;
		Inventory inventory;

		location.ReloadData(Data::ReadData("Saved data/Location.txt"));
		time.ReloadData(Data::ReadData("Saved data/Time.txt"));
		character.ReloadData(Data::ReadData("Saved data/Character.txt"));
		inventory.ReloadData(Data::ReadData("Saved data/Inventory.txt"));
	}
}

void Data::SaveAllStaticData()
{
	Location location;
	GeneralTime time;
	Character character;
	Inventory inventory;

	Data::SaveData("Saved data/Location.txt", location);
	Data::SaveData("Saved data/Time.txt", time);
	Data::SaveData("Saved data/Character.txt", character);
	Data::SaveData("Saved data/Inventory.txt", inventory);
	Data::ChangePossibilityDataSave();
}

void Data::SaveData(string fileLocation, IData& obj)
{
	fstream fs;
	fs.open(fileLocation, fstream::out);
	std::map<std::string, int> m = obj.WhatToSave();
	if (fs.is_open())
		for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it)
			fs << it->first << " " << it->second << endl;
	else
		cout << "File can't open";

	fs.close();
}

std::map<std::string, int> Data::ReadData(string fileLocation)
{
	fstream fs;
	fs.open(fileLocation, fstream::in);
	std::map<std::string, int> tempMap;

	if (fs.is_open())
	{
		string str;
		size_t pos = 0;
		string spaceDelimiter = " ";
		
		while (getline(fs, str))
			while ((pos = str.find(spaceDelimiter)) != string::npos)
			{
				tempMap[str.substr(0, pos)] = std::stoi(str.substr(pos+1, str.length()));
				str.erase(0, pos + spaceDelimiter.length());
			}
	}
	else
		cout << "File can't open";

	fs.close();
	return tempMap;
}

void Data::AvailDataReloading() { canSaveData = true; }
void Data::ForbidDataReloading() { canSaveData = false; }
bool Data::CanSaveData() { return canSaveData; }