#include "Character.h"
#include "Location.h"
#include "Inventory.h"
int Character::hunger = 100,
Character::thirst = 100,
Character::warmth = 100,
Character::energy = 100,
Character::condition = 100;
#include <math.h>
#include <iostream>
void Character::ChangeHungerLevel(int food)
{
	Character::hunger += food;
	if (Character::hunger > 100) Character::hunger = 100;
	if (Character::hunger < 0) Character::hunger = 0;
}
void Character::ChangeThirstLevel(int water)
{
	Character::thirst += water;
	if (Character::thirst > 100) Character::thirst = 100;
	if (Character::thirst < 0) Character::thirst = 0;
}
void Character::ChangeWarmthLevel(int warmth)
{
    Character::warmth += warmth;
	if (Character::warmth > 100) Character::warmth = 100;
	if (Character::warmth < 0) Character::warmth = 0;
}
void Character::ChangeEnergyLevel(int energy)
{
	if (energy > 0) Character::energy += energy * round((condition + warmth) / 200); // dependence between energy and warmth, condition
	if (energy < 0) Character::energy += energy * round(200 / (condition + warmth));  
	if (Character::energy > 100) Character::energy = 100;
	if (Character::energy < 0) Character::energy = 0;
}
void Character::ChangeConditionLevel(int points)
{
	if (points > 0) Character::condition += points * warmth / 100;
	if (points < 0) Character::condition += points * 100 / warmth;
	if (Character::condition > 100) Character::condition = 100;
	if (Character::condition < 0) Character::condition = 0;
}
void Character::Rest(int hours)
{
	Character::ChangeEnergyLevel(hours * 13); // sleeping for 8 hours will fully restore energy
	GeneralTime::AddTime(hours, 0);
	Character::ChangeThirstLevel(hours * -10);
	Character::ChangeHungerLevel(hours * -10);

	//test
	DisplayCharacteristics();
}
void Character::DisplayCharacteristics()
{
	cout << "Energy = " << Character::GetEnergyLevel() << endl
		<< "Hunger = " << Character::GetHungerLevel() << endl
		<< "Thirst = " << Character::GetThirstLevel() << endl
		<< "Condition = " << Character::GetConditionLevel() << endl
		<< "Warmth = " << Character::GetWarmthLevel() << endl;
	GeneralTime::DisplayCurrentTime();
	cout << "______________________________________________" << endl;
	Inventory::DisplayCharacteristics();
}
int Character::GetHungerLevel() { return hunger; }
int Character::GetThirstLevel() { return thirst; }
int Character::GetWarmthLevel() { return warmth; }
int Character::GetEnergyLevel() { return energy; }
int Character::GetConditionLevel() { return condition; }

int Character::CheckIFCharacteristicsBelowZero()
{
	if ((hunger * thirst * warmth * energy * condition) == 0)
		return 0;
	else return 1;
}

#pragma region InterfaceRealisation

void Character::ReloadData(map<string, int> data)
{
	hunger = data["Hunger"];
	thirst = data["Thirst"];
	warmth = data["Warmth"];
	energy = data["Energy"];
	condition = data["Condition"];
}

std::map<std::string, int> Character::WhatToSave()
{
	std::map<std::string, int> Save =
	{
		{"Hunger", hunger},
		{"Thirst", thirst},
		{"Warmth", warmth},
		{"Energy", energy},
		{"Condition", condition}
	};
	return Save;
}

void Character::DisplayStats()
{
	cout << "Hunger: " << hunger << endl;
	cout << "Thirst: " << thirst << endl;
	cout << "Warmth: " << warmth << endl;
	cout << "Energy: " << energy << endl;
	cout << "Condition: " << condition << endl;
}

void Character::SetDeffaultCharacteristics()
{
	hunger = 100;
	thirst = 100;
	warmth = 100;
	energy = 100;
	condition = 100;
}

#pragma endregion