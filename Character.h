#include <iostream>
#include "Interfaces.h"

class Character : public IData
{
public:
	static void ChangeHungerLevel(int food);
	static void ChangeThirstLevel(int water);
	static void ChangeWarmthLevel(int warmth);
	static void ChangeEnergyLevel(int energy);
	static void ChangeConditionLevel(int points);
	static int GetHungerLevel();
	static int GetThirstLevel();
	static int GetWarmthLevel();
	static int GetEnergyLevel();
	static int GetConditionLevel();
	static void Rest(int hours);
	static void DisplayCharacteristics();
	static bool CheckIFCharacteristicsBelowZero();
	static bool IsStayAtFire();
	static void SetStayAtFire(bool value);

	void ReloadData(std::map<std::string, int> data) override;
	void DisplayStats() override;
	void SetDeffaultCharacteristics() override;
	std::map<std::string, int> WhatToSave() override;

	int static startedHour;
	int static startedDay;
private:
	int static hunger;
	int static thirst;
	int static warmth;
	int static energy;
	int static condition;
	bool static isStayAtFire;
};



