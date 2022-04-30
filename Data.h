#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include "Interfaces.h"

using namespace std;

class Data
{
public:
	static int GetEnvironment(int index);

	template<typename T>
	static void DisplayData(string fileLocation, IData& obj);
	static void SaveData(string fileLocation, IData& obj);
	static std::map<std::string, int> ReadData(string fileLocation);

	static void SaveAllStaticData();
	static void ReloadAllStaticData();
	static void SaveGamePerSomeTime(int someHour);

	static void AvailDataReloading();
	static void ForbidDataReloading();
	static bool CanSaveData();
protected:
	static std::list<int> EnvironmentsSequence;
	static bool canSaveData;
	static void ReloadPossibilityDataSave();
	static void ChangePossibilityDataSave();
	static int startedHour;
	static int stardedDay;
};

template<typename T>
void Data::DisplayData(string fileLocation, IData& obj)
{
	fstream fs;
	fs.open(fileLocation, fstream::in);

	if (fs.is_open())
	{
		T object;
		while (fs.read((char*)&object, sizeof(T)))
			object.DisplayStats();
	}
	else
		cout << "File doesn't open";

	fs.close();
}