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
		{"axe", true},
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
void Inventory::ExploreArea(int counterClick)
{
	int lucky = 0;
	if (Check_Tool("map")) lucky = 2;
	if (Check_Tool("flashlight")) lucky = 3;
	srand(time(0));
	if (2 + lucky - counterClick > 0) tools["matches"] = rand() % (2 + lucky - counterClick);
	if (2 + lucky - counterClick > 0) tools["flashlight"] = rand() % (2 + lucky - counterClick);
	if (2 + lucky - counterClick > 0) tools["rope"] = rand() % (2 + lucky - counterClick);
	if (1 + lucky - counterClick>0) food += rand() % (1+lucky - counterClick);
	if (5 + lucky - counterClick > 0) water += rand() % (5 + lucky - counterClick);
	if (3 + lucky - counterClick>0) tinder += rand() % (3 + lucky - counterClick);
	if (2 + lucky - counterClick > 0) medicine += rand() % (2 + lucky - counterClick);
	Character::ChangeEnergyLevel(-15);
	GeneralTime::AddTime(0, 30);
	Character::ChangeHungerLevel(-5);
	Character::ChangeThirstLevel(-7);
	if (counterClick == 1) Generator::GenerateEnvironments(3, 3);
	Character::DisplayCharacteristics();
}
void Inventory::LoseInventory()
{
	srand(time(0));
	if (Check_Tool("axe") && !(rand() % 10)) tools["axe"] = 0;
	if (Check_Tool("flashlight") && !(rand() % 4)) tools["flashlight"] = 0;
	if (Check_Tool("lighter") && !(rand() % 4)) tools["lighter"] = 0;
	if (Check_Tool("fishing rod") && rand() % 2) tools["fishing rod"] = 0;
	if (Check_Tool("compass") && !(rand() % 4)) tools["compass"] = 0;
	if (Check_Tool("map") && !(rand() % 5)) tools["map"] = 0;
	if (Check_Tool("matches") && rand() % 2) tools["matches"] = 0;
	if (Check_Tool("lens") && !(rand() % 4)) tools["lens"] = 0;
	if (Check_Tool("knife") && !(rand() % 3)) tools["knife"] = 0;
	if (Check_Tool("rope") && rand() % 2) tools["rope"] = 0;
	if (Check_Tool("spear") && !(rand() % 3)) tools["spear"] = 0;
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

void Inventory::SetDeffaultCharacteristics()
{
	food = 1;
	water = 1;
	wood = 0;
	tinder = 0;
	medicine = 0;
	Inventory::tools["axe"] = 1;
	Inventory::tools["flashlight"] = 0;
	Inventory::tools["lighter"] = 1;
	Inventory::tools["fishing rod"] = 1;
	Inventory::tools["compass"] = 0;
	Inventory::tools["map"] = 1;
	Inventory::tools["matches"] = 0;
	Inventory::tools["lens"] = 0;
	Inventory::tools["knife"] = 0;
	Inventory::tools["rope"] = 0;
	Inventory::tools["spear"] = 1;
	Inventory::tools["spring trap"] = 1;
	Inventory::tools["bird trap"] = 1;
	Inventory::tools["fall trap"] = 1;
}

#pragma endregion

int Inventory::ReturnNumberOfItems(string item_name)
{
	if (item_name == "food")
		return food;
	if (item_name == "water")
		return water;
	if (item_name == "wood")
		return wood;
	if (item_name == "tinder")
		return tinder;
	if (item_name == "medicine")
		return medicine;
}