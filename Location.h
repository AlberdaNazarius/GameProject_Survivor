#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Data.h"

using namespace std;

class Environment
{
public:
	Environment() {}
	virtual ~Environment() {}
	void SetBackground(sf::Sprite &sprite, sf::Texture &texture, std::string picture, int windowWidth, int windowHeight);
protected:
	int index; // every environment has a specific index
	map<string, int> animals;
};

class Forest : public Environment
{
public:
	Forest();
	~Forest() {}
	void static ExploreArea(); // It must be override method of class Actions
	void static Hunt(); // It must be override method of class Actions
	void static SetPicture(std::string picture);
	std::string static GetPicture();
private:
	static std::string picture; // picture name
};

class Lake: public Environment 
{
public:
	Lake();
	~Lake() {}
	void static ExploreArea(); // It must be override method of class Actions
	void static Hunt(); // It must be override method of class Actions
	void static SetPicture(std::string picture);
	std::string static GetPicture();
private:
	static std::string picture; // picture name
};

class River : public Environment 
{
public:
	River();
	~River() {}
	void static ExploreArea();
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
	static int LocationCurrent;
	static void CheckWhatEnvironment(int environmentIndex);
	void SetWindowResolution(int windowWidth, int windowHeight);

	static sf::Sprite Sprite;

	//void static SavedData();
private:
	static sf::Texture texture;
	int temperature;
	static int windowWidth;  
	static int windowHeight;
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