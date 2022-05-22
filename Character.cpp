#include <math.h>
#include <iostream>
#include "Character.h"
#include "Location.h"
#include "Inventory.h"

int Character::hunger = 100;
int	Character::thirst = 100;
int	Character::warmth = 100;
int	Character::energy = 100;
int	Character::condition = 100;
bool Character::isStayAtFire = 0;
int Character::startedHour = 0;
int Character::startedDay = 0;


void Character::ChangeHungerLevel(int food)
{
	Character::hunger += food;
	if (Character::hunger > 100) Character::hunger = 100;
	if (Character::hunger < 0) Character::hunger = 0;
	if (food > 0) Character::ChangeEnergyLevel(round(food / 2));
}
void Character::ChangeThirstLevel(int water)
{
	Character::thirst += water;
	if (Character::thirst > 100) Character::thirst = 100;
	if (Character::thirst < 0) Character::thirst = 0;
	if (water > 0) Character::ChangeEnergyLevel(round(water / 2));
}
void Character::ChangeWarmthLevel(int warmth)
{
    Character::warmth += warmth;
	Character::ChangeConditionLevel(warmth / 2);
	if (Character::condition > 100) Character::condition = 100;
	if (Character::warmth > 100) Character::warmth = 100;
	if (Character::warmth < 0) Character::warmth = 0;
	
}
void Character::ChangeEnergyLevel(int energy)
{
	if (energy > 0) Character::energy += round(energy * (condition + warmth) / 200); // dependence between energy and warmth, condition
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
	GeneralTime::AddTime(hours, 0);
	Character::ChangeEnergyLevel(13 * hours); // sleeping for 8 hours will fully restore energy
	Character::ChangeThirstLevel(-5 * hours);
	Character::ChangeHungerLevel(-7 * hours);

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

bool Character::CheckIFCharacteristicsBelowZero()
{
	if ((hunger * thirst * warmth * energy * condition) == 0)
		return true;
	else return false;
}

bool Character::IsStayAtFire()
{
	return isStayAtFire;
}

void Character::SetStayAtFire(bool value)
{
	isStayAtFire = value;
}

#pragma region InterfaceRealisation

void Character::ReloadData(map<string, int> data)
{
	hunger = data["Hunger"];
	thirst = data["Thirst"];
	warmth = data["Warmth"];
	energy = data["Energy"];
	condition = data["Condition"];
	isStayAtFire = data["IsStayAtFire"];
	startedHour = data["StartedHour"];
	startedDay = data["StartedDay"];
}

std::map<std::string, int> Character::WhatToSave()
{
	std::map<std::string, int> Save =
	{
		{"Hunger", hunger},
		{"Thirst", thirst},
		{"Warmth", warmth},
		{"Energy", energy},
		{"Condition", condition},
		{"IsStayAtFire", isStayAtFire},
		{"StartedHour", startedHour},
		{"StartedDay", startedDay}
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
	cout << "SsStayAtFire: " << isStayAtFire << endl;

}

void Character::SetDeffaultCharacteristics()
{
	hunger = 100;
	thirst = 100;
	warmth = 100;
	energy = 100;
	condition = 100;
	isStayAtFire = 0;
	startedHour = 0;
	startedDay = 0;
}

#pragma endregion