#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "Data.h"
#include "Interfaces.h"
using namespace sf;
using namespace std;
class Environment
{
public:
	Environment() {	}
	virtual ~Environment() {}
	void SetBackground(sf::Sprite& sprite, sf::Texture& texture, string picture, int windowWidth, int windowHeight);
	map<int, string>::iterator Hunt(int maxIndexOfGeneration);
	map<int, string> animals;
protected:
	int index; // every environment has a specific index

};

class Forest : public Environment
{
public:
	Forest();
	~Forest() {}
	void static SetPicture(std::string picture);
	string static GetPicture();
private:
	static string picture; // picture name
};

class Lake : public Environment
{
public:
	Lake();
	~Lake() {}
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
	void static SetPicture(std::string picture);
	std::string static GetPicture();
private:
	static std::string picture; // picture name
};

class Location : public IData
{
public:
	static Environment* CurrentLocation;
	static int LocationCurrent;
	static void CheckWhatEnvironment(int environmentIndex);
	static void SetBackground(string picture);

	static sf::Sprite Sprite;
	static int GetTemperature();
	static void ChangeTemperature(int gradus);
	static bool Shelter;

	void ReloadData(map<std::string, int> data) override;
	void DisplayStats() override;
	void SetDeffaultCharacteristics() override;
	std::map<std::string, int> WhatToSave() override;

	~Location() { delete[] CurrentLocation; }
private:
	static sf::Image image;
	static sf::Texture texture;
	static int temperature;
	static int windowWidth;
	static int windowHeight;
};

class GeneralTime : public IData
{
public:
	static void DisplayCurrentTime();
	static void AddTime(int hours, int minutes);
	static int DeltaTime(int startedDay, int startedHour);
	static string GetTime();
	static int GetDay();
	static int GetHours();
	static int GetMinutes();

	void ReloadData(map<std::string, int> data) override;
	void DisplayStats() override;
	void SetDeffaultCharacteristics() override;
	std::map<std::string, int> WhatToSave() override;
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
