#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Environment
{
public:
	virtual ~Environment() {}
	void SetBackground(sf::Sprite &sprite, sf::Texture &texture, std::string picture, int windowWidth, int windowHeight);
	int GetIndex();
	void Picture(std::string picture) { this->picture = picture; }
	std::string Picture() { return picture; }
protected:
	int time;
	int index; // every environment has a specific index
	std::string picture; // picture name
};

class Forest : public Environment // also must inherit class Actions
{
public:
	Forest() { index = 1; }
	~Forest() {}
	void static ExploreArea(); // It must be override method of class Actions
	void static Hunt(); // It must be override method of class Actions
};

class Lake: public Environment // also must inherit class Actions
{
public:
	Lake() { index = 2; }
	~Lake() {}
	void static ExploreArea(); // It must be override method of class Actions
	void static Hunt(); // It must be override method of class Actions
};

class Location
{
public:
	sf::Sprite Sprite;
	void static SavedData();
	void CheckWhatEnvironment(Environment* environment);
	void SetWindowResolution(int windowWidth, int windowHeight);
private:
	sf::Texture texture;
	int data;// not int maybe it will be class Data
	int windowWidth = 1920;
	int windowHeight = 1080;
};