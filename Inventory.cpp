#include "Inventory.h"
#include "Character.h"
#include "Location.h"
#include <ctime>
#include <iostream> // for testing

int  Inventory::food = 1,
Inventory::water = 1,
Inventory::wood = 0,
Inventory::tinder = 0,
Inventory::medicine = 0;

map<string, bool> Inventory::tools = {
		{"axe", false},
		{"flashlight", false},
		{"lighter", true},
		{"fishing rod", true},
		{"compass", false},
		{"map", true},
		{"matches", false},
		{"lens", false},
		{"knife", false},
		{"rope", false},
		{"spear", true},
		{"spring trap", true},
		{"bird trap", true},
		{"fall trap", true},
};
bool Inventory::Check_Tool(string tool_id)
{
	return tools[tool_id];
}
void Inventory::ExploreArea()
{
	srand(time(0));
	tools["matches"] = rand() % 2;
	tools["flashlight"] = rand() % 2;
	food += rand() % 3; 
	water += rand() % 3; 
	wood += rand() % 3; 
	tinder += rand() % 3; 
	medicine += rand() % 3; 
	Character::ChangeEnergyLevel(-15);
	GeneralTime::AddTime(0, 30);
	Character::ChangeHungerLevel(-5);
	Character::ChangeThirstLevel(-7);
	Generator::GenerateEnvironments(3, 3);
	Character::DisplayCharacteristics();
}
void Inventory::Change_Item(string item_name, int number)
{
	if (item_name == "food")	food += number;
	else
	{
		tools[item_name] = number;
	}
	if (item_name == "water")	water += number;
	else
	{
		tools[item_name] = number;
	}
	if (item_name == "wood")	wood += number;
	else
	{
		tools[item_name] = number;
	}
	if (item_name == "tinder")	tinder += number;
	else
	{
		tools[item_name] = number;
	}
	if (item_name == "medicine")	medicine += number;
	else
	{
		tools[item_name] = number;
	}
}
void Inventory::DisplayCharacteristics()
{
	for (auto it = tools.begin(); it != tools.end(); it++)
		cout << it->first << " = " << it->second << endl;
	cout << "food = " << food << endl
		<< "water = " << water << endl
		<< "wood = " << wood << endl
		<< "tinder = " << tinder << endl
		<< "medicine = " << medicine << endl; 
	cout << "______________________________________________" << endl;
}
#pragma region InterfaceRealisation

std::map<std::string, int> Inventory::WhatToSave()
{
	std::map<std::string, int> Save =
	{
		{"Food", food},
		{"Water", water},
		{"Wood", wood},
		{"Tinder", tinder},
		{"Medicine", medicine},
		{"Axe", (int)Inventory::tools["axe"]},
		{"Flashlight", (int)Inventory::tools["flashlight"]},
		{"Lighter", Inventory::tools["lighter"]},
		{"FishingRod", (int)Inventory::tools["fishing rod"]},
		{"Compass", (int)Inventory::tools["compass"]},
		{"Map", (int)Inventory::tools["map"]},
		{"Matches", (int)Inventory::tools["matches"]},
		{"Lens", (int)Inventory::tools["lens"]},
		{"Knife", (int)Inventory::tools["knife"]},
		{"Rope", (int)Inventory::tools["rope"]},
		{"Spear", (int)Inventory::tools["spear"]},
		{"SpringTrap", (int)Inventory::tools["spring trap"]},
		{"BirdTrap", (int)Inventory::tools["bird trap"]},
		{"FallTrap", (int)Inventory::tools["fall trap"]}
	};
	return Save;
}

void  Inventory::ReloadData(map<string, int> data)
{
	food = data["Food"];
	water = data["Water"];
	wood = data["Wood"];
	tinder = data["Tinder"];
	medicine = data["Medicine"];
	Inventory::tools["axe"] = data["Axe"];
	Inventory::tools["flashlight"] = data["Flashlight"];
	Inventory::tools["lighter"] = data["Lighter"];
	Inventory::tools["fishing rod"] = data["FishingRod"];
	Inventory::tools["compass"] = data["Compass"];
	Inventory::tools["map"] = data["Map"];
	Inventory::tools["matches"] = data["Matches"];
	Inventory::tools["lens"] = data["Lens"];
	Inventory::tools["knife"] = data["Knife"];
	Inventory::tools["rope"] = data["Rope"];
	Inventory::tools["spear"] = data["Spear"];
	Inventory::tools["spring trap"] = data["SpringTrap"];
	Inventory::tools["bird trap"] = data["BirdTrap"];
	Inventory::tools["fall trap"] = data["FallTrap"];
}

void Inventory::DisplayStats()
{
	cout << "Food = " << food;
	cout << "Water = " << water;
	cout << "Wood = " << wood;
	cout << "Tinder = " << tinder;
	cout << "Medicine = " << medicine;
}

#pragma endregion