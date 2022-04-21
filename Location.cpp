#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Location.h"
#include "Data.h"

using namespace std;

Environment* Location::CurrentLocation;
std::list<int> Data::EnvironmentsSequence;

void Location::CheckWhatEnvironment(int environmentIndex)
{
	
	if (environmentIndex == 1)
	{
		auto forest = (Forest*)Location::CurrentLocation;
		forest->ExploreArea();
		forest->Hunt();
		forest->SetBackground(Sprite, texture, Forest::GetPicture(), windowWidth, windowHeight);
		//forest->SetBackground(Sprite, texture, Lake::picture, windowWidth, windowHeight);
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

// Getters and setters for Forest picture 
void Forest::SetPicture(std::string picture) { Forest::picture = picture; }
std::string Forest::GetPicture() { return Forest::picture;  }
std::string Forest::picture;
// Getters and setters for Lake picture 
void Lake::SetPicture(std::string picture) { Lake::picture = picture; }
std::string Lake::GetPicture() { return Lake::picture;  }
std::string Lake::picture;

void Generator::GenerateEnvironments(int maxIndex, int amount)
{
	srand(time(0));
	for (int i = 0; i < amount; i++)//make random creation of environments
	{
		int randIndex = 1 + rand() % maxIndex;
		Data::EnvironmentsSequence.push_back(randIndex);
	}
}

void Generator::PrintGeneratedEnvironments()
{
	list<int>::iterator it;
	for (it = Data::EnvironmentsSequence.begin();it != Data::EnvironmentsSequence.end();it++)
		std::cout << *it << " ";
}

#pragma region MyRegion
void Location::SetWindowResolution(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

void Location::SavedData()
{
	// realisation
}

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