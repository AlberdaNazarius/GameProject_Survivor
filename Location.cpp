#include <SFML/Graphics.hpp>
#include "Location.h"

#pragma region StaticVariables

Environment* Location::CurrentLocation;
std::list<int> Data::EnvironmentsSequence;
int GeneralTime::minutes;
int GeneralTime::hours;
int GeneralTime::days;
sf::Sprite Location::Sprite;
sf::Texture Location::texture;
sf::Image Location::image;

std::string picture;
int Location::LocationCurrent;
int Location::temperature;
bool Location::Shelter;
int Location::windowWidth = 1920;
int Location::windowHeight = 1080;
#pragma endregion

void Location::CheckWhatEnvironment(int environmentIndex)
{
	if (environmentIndex == 1)
	{
		auto forest = (Forest*)Location::CurrentLocation;
		Location::SetBackground(Forest::GetPicture());
	}
	if (environmentIndex == 2)
	{
		auto lake = (Lake*)Location::CurrentLocation;
		Location::SetBackground(Lake::GetPicture());
	}
	if (environmentIndex == 3)
	{
		auto river = (River*)Location::CurrentLocation;
		Location::SetBackground(River::GetPicture());
	}
}

void Location::SetBackground(string picture)
{
	if (picture.size() >= 1)
	{
		Location::image.loadFromFile(picture);
		Location::texture.loadFromImage(image, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)image.getSize()));
		Location::Sprite.setTexture(texture);
	}
	else
		cout << "Picture isn't loaded!";
}

string GeneralTime::GetTime()
{
	if (GetHours() < 10 && GetMinutes() < 10)
		return to_string(GetDay()) + ":0" + to_string(GetHours()) + ":0" + to_string(GetMinutes());
	else if (GetMinutes() < 10)
		return to_string(GetDay()) + ":" + to_string(GetHours()) + ":0" + to_string(GetMinutes());
	else if (GetHours() < 10)
		return to_string(GetDay()) + ":0" + to_string(GetHours()) + ":" + to_string(GetMinutes());
	else
		return to_string(GetDay()) + ":" + to_string(GetHours()) + ":" + to_string(GetMinutes());
}

map<int, string>::iterator Environment::Hunt(int maxIndexOfGeneration)
{
	auto it = animals.begin();
	srand(time(0));
	std::vector<int> random;
	std::vector<int> probability;
	int counter = 0;
	int max = 0;
	for (int i = 0; i < animals.size(); i++)
		random.push_back(rand() % maxIndexOfGeneration);
	do
	{
		for (int value : random)
			if (value == maxIndexOfGeneration - 1)
				counter++;
		probability.push_back(counter);
		counter = 0;
		maxIndexOfGeneration--;
	} while (maxIndexOfGeneration);
	for (int value : probability)
		if (value > max)
			max = value;
	for (int i = 0; i < max - 1; i++)
	{
		++it;
	}
//	cout << it->second << endl;
	return it;
}


int Location::GetTemperature() { return temperature; }

void Location::ChangeTemperature(int gradus)
{
	temperature += gradus;
	if (temperature > 30)
		Location::ChangeTemperature(Generator::GenerateTemperature(-10, 5));
	if (temperature < -15)
		Location::ChangeTemperature(Generator::GenerateTemperature(5, 10));
}


// Interface realisation
std::map<std::string, int> Location::WhatToSave()
{
	std::map<std::string, int> Save =
	{
		{"Temperature", GetTemperature()},
		{"Shelter", Shelter},
		{"LocationCurrent", LocationCurrent}
	};
	return Save;
}

void  Location::ReloadData(map<string, int> data)
{
	temperature = data["Temperature"];
	Shelter = data["Shelter"];
	LocationCurrent = data["LocationCurrent"];
}

void Location::DisplayStats()
{
	cout << "Temperature: " << GetTemperature();
}

void Location::SetDeffaultCharacteristics()
{
	temperature = 10;
	Shelter = 0;
}

std::map<std::string, int> GeneralTime::WhatToSave()
{
	std::map<std::string, int> Save =
	{
		{"Days", days},
		{"Hours", hours},
		{"Minutes", minutes}
	};
	return Save;
}

void  GeneralTime::ReloadData(map<string, int> data)
{
	days = data["Days"];
	hours = data["Hours"];
	minutes = data["Minutes"];
}

void GeneralTime::DisplayStats()
{
	cout << "Days: " << GetDay() << endl;
	cout << "Hours: " << GetHours() << endl;
	cout << "Minutes: " << GetMinutes() << endl;
}

void GeneralTime::SetDeffaultCharacteristics()
{
	days = 0;
	hours = 6;
	minutes = 30;
}
//////


#pragma region ForestAndLake 

// Getters and setters for Forest picture 
void Forest::SetPicture(std::string picture) { Forest::picture = picture; }
std::string Forest::GetPicture() { return Forest::picture; }
std::string Forest::picture;

// Getters and setters for Lake picture 
void Lake::SetPicture(std::string picture) { Lake::picture = picture; }
std::string Lake::GetPicture() { return Lake::picture; }
std::string Lake::picture;

// Getters and setters for River picture 
void River::SetPicture(std::string picture) { River::picture = picture; }
std::string River::GetPicture() { return River::picture; }
std::string River::picture;

Forest::Forest() : Environment()
{
	index = 1;
	animals =
	{
		{ 3, "Bird"},
		{ 4, "Squirrel"},
		{ 5, "Hare"},
		{ 6, "Fox"},
		{ 8, "Deer"},
	};
}

Lake::Lake() : Environment()
{
	index = 2;
	animals =
	{
		{ 5, "Duck"},
		{ 4, "Fish"},
		{ 3, "Fog"},
	};
}

River::River() : Environment()
{
	index = 3;
	animals =
	{
		{ 5, "Beaver"},
		{ 4, "Fish"},
	};
}

#pragma endregion

#pragma region Generator

void Generator::GenerateEnvironments(int maxIndex, int amount)
{
	srand(time(0));
	Data::EnvironmentsSequence.clear();
	for (int i = 0; i < amount; i++)//make random creation of environments
	{
		int randIndex = 1 + rand() % maxIndex;
		Data::EnvironmentsSequence.push_back(randIndex);
	}
}

int Generator::GenerateTemperature(int minTemperature, int maxTemperature)
{
	srand(time(0));
	int randTemperature = minTemperature + (rand() % maxTemperature);
	return randTemperature;
}

void Generator::PrintGeneratedEnvironments()
{
	list<int>::iterator it;
	for (it = Data::EnvironmentsSequence.begin(); it != Data::EnvironmentsSequence.end(); it++)
		std::cout << *it << " ";
}

#pragma endregion

#pragma region Time

int GeneralTime::GetDay() { return days; }
int GeneralTime::GetHours() { return hours; }
int GeneralTime::GetMinutes() { return minutes; }

void GeneralTime::DisplayCurrentTime() { cout << hours << ":" << minutes << std::endl; }
int GeneralTime::DeltaTime(int startedDay, int startedHour) { return ((days * 24) + hours) - ((startedDay * 24) + startedHour); }

void GeneralTime::AddTime(int hours, int minutes)
{
	if (hours >= 24) throw("You set too much hours!");

	GeneralTime::hours += hours;
	GeneralTime::minutes += minutes;
	// Convert minutes to hours and resets the minutes count
	if (GeneralTime::minutes >= 60)
	{
		int deltaHour = (int)GeneralTime::minutes / 60;
		GeneralTime::hours += deltaHour;
		GeneralTime::minutes -= deltaHour * 60;
	}

	// Resets the hours count
	if (GeneralTime::hours >= 24)
	{
		GeneralTime::days++; // Add day
		GeneralTime::hours -= 24;
	}
}

#pragma endregion