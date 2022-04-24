#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Location.h"
#include "Data.h"

using namespace std;

#pragma region StaticVariables

Environment* Location::CurrentLocation;
std::list<int> Data::EnvironmentsSequence;
int GeneralTime::minutes;
int GeneralTime::hours;
int GeneralTime::days;

#pragma endregion

void Location::CheckWhatEnvironment(int environmentIndex)
{
	if (environmentIndex == 1)
	{
		auto forest = (Forest*)Location::CurrentLocation;
		forest->ExploreArea();
		forest->Hunt();
		forest->SetBackground(Sprite, texture, Forest::GetPicture(), windowWidth, windowHeight);
	}
	if (environmentIndex == 2)
	{
		auto lake = (Lake*)Location::CurrentLocation;
		lake->ExploreArea();
		lake->Hunt();
		lake->SetBackground(Sprite, texture, Lake::GetPicture(), windowWidth, windowHeight);
	}
}

void Environment::SetBackground(sf::Sprite &sprite, sf::Texture &texture, string picture, int windowWidth, int windowHeight)
{
	if (picture.size() >= 1)
	{
		texture.loadFromFile(picture, sf::IntRect(0, 0, windowWidth, windowHeight));
		sprite.setTexture(texture);
	}
	else
		throw "Picture isn't set!";
}

void Location::SetWindowResolution(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

#pragma region ForestAndLake 

// Getters and setters for Forest picture 
void Forest::SetPicture(std::string picture) { Forest::picture = picture; }
std::string Forest::GetPicture() { return Forest::picture;  }
std::string Forest::picture;

// Getters and setters for Lake picture 
void Lake::SetPicture(std::string picture) { Lake::picture = picture; }
std::string Lake::GetPicture() { return Lake::picture;  }
std::string Lake::picture;

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
	int randTemperature = minTemperature + (rand() % (maxTemperature - minTemperature));
	return randTemperature;
}
void Generator::PrintGeneratedEnvironments()
{
	list<int>::iterator it;
	for (it = Data::EnvironmentsSequence.begin();it != Data::EnvironmentsSequence.end();it++)
		std::cout << *it << " ";
}

#pragma endregion

#pragma region Time

int GeneralTime::GetDay() { return days; }
int GeneralTime::GetHours() { return hours; }
int GeneralTime::GetMinutes() { return minutes; }

void GeneralTime::DisplayCurrentTime() { cout << hours << ":" << minutes << std::endl; }
int GeneralTime::DeltaTime(int startedDay, int startedHour) { return ((GeneralTime::days * 24) + hours) - ((startedDay * 24) + startedHour); }

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

#pragma region NeedRealisation

void Forest::ExploreArea() // It must be overload method
{
	// realisation
}
void Lake::ExploreArea() // It must be overload method
{
	// realisation
}

void Forest::Hunt() // It must be overload method
{
	// realisation
}

void Lake::Hunt() // It must be overload method
{
	// realisation
}

#pragma endregion