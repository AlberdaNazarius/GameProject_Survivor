#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Location.h"
using namespace std;

void Location::CheckWhatEnvironment(Environment* environment)
{
	if (environment->GetIndex() == 1)
	{
		auto forest = (Forest*)environment;
		forest->ExploreArea();
		forest->Hunt();
		forest->SetBackground(Sprite, texture, forest->Picture(), windowWidth, windowHeight);
	}
	if (environment->GetIndex() == 2)
	{
		auto lake = (Lake*)environment;
		lake->ExploreArea();
		lake->Hunt();
		lake->SetBackground(Sprite, texture, lake->Picture(), windowWidth, windowHeight);
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

int Environment::GetIndex() { return index; }

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