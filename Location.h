#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Data.h"

class Environment
{
public:
	Environment() {}
	virtual ~Environment() {}
	void SetBackground(sf::Sprite &sprite, sf::Texture &texture, std::string picture, int windowWidth, int windowHeight);
protected:
	int index; // every environment has a specific index
};

class Forest : public Environment // also must inherit class Actions
{
public:
	Forest() { index = 1; }
	~Forest() {}
	void static ExploreArea(); // It must be override method of class Actions
	void static Hunt(); // It must be override method of class Actions
	void static SetPicture(std::string picture);
	std::string static GetPicture();
private:
	static std::string picture; // picture name
};

class Lake: public Environment // also must inherit class Actions
{
public:
	Lake() { index = 2; }
	~Lake() {}
	void static ExploreArea(); // It must be override method of class Actions
	void static Hunt(); // It must be override method of class Actions
	void static SetPicture(std::string picture);
	std::string static GetPicture();
private:
	static std::string picture; // picture name
};

class Location
{
public:
	static Environment* CurrentLocation;
	void CheckWhatEnvironment(int environmentIndex);
	void SetWindowResolution(int windowWidth, int windowHeight);

	sf::Sprite Sprite;

	//void static SavedData();
private:
	sf::Texture texture;
	int temperature;
	int windowWidth = 1920;
	int windowHeight = 1080;
};

class GeneralTime
{
public:
	static void DisplayCurrentTime();
	static void AddTime(int hours, int minutes);
	static int DeltaTime(int startedDay, int startedHour);
	static int GetDay();
	static int GetHours();
	static int GetMinutes();
private:
	static int days;
	static int hours;
	static int minutes;
};

class Generator : protected Data
{
public:
	static void GenerateEnvironments(int maxIndex, int amount);
	static void PrintGeneratedEnvironments();
	static int GenerateTemperature(int minTemperature, int maxTemperature);
};