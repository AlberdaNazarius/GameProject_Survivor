#include "Inventory.h"
#include "Character.h"
#include "Location.h"
#include <ctime>
#include <sstream>
#include <iostream> // for testing

int  Inventory::food = 1,
Inventory::water = 1,
Inventory::wood = 0,
Inventory::tinder = 0,
Inventory::medicine = 0,
Inventory::rope = 0,
Inventory::checkClickExploreArea = 0;

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
		{"spear", true},
		{"spring trap", true},
		{"bird trap", true},
		{"fall trap", true},
};
bool Inventory::Check_Tool(string tool_id)
{
	return tools[tool_id];
}
string Inventory::ExploreArea(int counterClick)
{
	string result, difference;
	int previousValue;
	int differenceValue;
	int lucky = 0;
	if (Check_Tool("map")) lucky = 2;
	if (Check_Tool("flashlight")) lucky = 3;
	srand(time(0));
	if (2 + lucky - counterClick > 0)
	{
		previousValue = tools["matches"];
		tools["matches"] = rand() % (2 + lucky - counterClick);
		differenceValue = tools["matches"] - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0) result = "Matches+" + difference;

	}
	if (2 + lucky - counterClick > 0)
	{
		previousValue = tools["flashlight"];
		tools["flashlight"] = rand() % (2 + lucky - counterClick);
		differenceValue = tools["flashlight"] - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0)
			if (result == "") result += "Flashlight+" + difference;
			else result += "\nFlashlight+" + difference;
	}
	if (2 + lucky - counterClick > 0)
	{
		previousValue = rope;
		rope = rand() % (2 + lucky - counterClick);
		differenceValue = rope - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0)
			if (result == "") result += "Rope+" + difference;
			else result += "\nRope+" + difference;
	}
	if (1 + lucky - counterClick > 0)
	{
		previousValue = food;
		food += rand() % (1 + lucky - counterClick);
		differenceValue = food - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0)
			if (result == "") result += "Food+" + difference;
			else result += "\nFood+" + difference;
	}
	if (5 + lucky - counterClick > 0)
	{
		previousValue = water;
		water += rand() % (5 + lucky - counterClick);
		differenceValue = water - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0)
			if (result == "") result += "Water+" + difference;
			else result += "\nWater+" + difference;
	}
	if (3 + lucky - counterClick > 0)
	{
		previousValue = tinder;
		tinder += rand() % (3 + lucky - counterClick);
		differenceValue = tinder - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0)
			if (result == "") result += "Tinder+" + difference;
			else  result += "\nTinder+" + difference;
	}
	if (2 + lucky - counterClick > 0)
	{
		previousValue = medicine;
		medicine += rand() % (2 + lucky - counterClick);
		differenceValue = medicine - previousValue;
		stringstream temp;
		temp << differenceValue;
		temp >> difference;
		if (differenceValue > 0) 
			if (result == "") result += "Medicine+" + difference;
			else result += "\nMedicine+" + difference;
	}

	if (counterClick == 1) Generator::GenerateEnvironments(3, 3);
	return result;
}
string Inventory::LoseInventory()
{
	string result;
	srand(time(0));
	if (Check_Tool("axe") && !(rand() % 10))
	{
		tools["axe"] = 0;
		result = "\nAxe-1";
	}
	if (Check_Tool("flashlight") && !(rand() % 10))
	{
		tools["flashlight"] = 0;
		result += "\nFlashlight-1";
	}
	if (Check_Tool("lighter") && !(rand() % 10))
	{
		tools["lighter"] = 0;
		result += "\nLighter-1";
	}
	if (Check_Tool("fishing rod") && !(rand() % 10))
	{
		tools["fishing rod"] = 0;
		result += "\nFishing rod-1";
	}
	if (Check_Tool("compass") && !(rand() % 10))
	{
		tools["compass"] = 0;
		result += "\nCompass-1";
	}
	if (Check_Tool("map") && !(rand() % 10))
	{
		tools["map"] = 0;
		result += "\nMap-1";
	}
	if (Check_Tool("matches") && !(rand() % 10))
	{
		tools["matches"] = 0;
		result += "\nMatches-1";
	}
	if (Check_Tool("lens") && !(rand() % 10))
	{
		tools["lens"] = 0;
		result += "\nLens-1";
	}
	if (Check_Tool("knife") && !(rand() % 10))
	{
		tools["knife"] = 0;
		result += "\nKnife-1";
	}
	if (Check_Tool("spear") && !(rand() % 10))
	{
		tools["spear"] = 0;
		result += "\nSpear-1";
	}
	return result;
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
	if (item_name == "rope")	rope += number;
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
		{"CheckClickExploreArea", checkClickExploreArea},
		{"Food", food},
		{"Water", water},
		{"Wood", wood},
		{"Tinder", tinder},
		{"Medicine", medicine},
		{"Rope", rope},
		{"Axe", (int)Inventory::tools["axe"]},
		{"Flashlight", (int)Inventory::tools["flashlight"]},
		{"Lighter", Inventory::tools["lighter"]},
		{"FishingRod", (int)Inventory::tools["fishing rod"]},
		{"Compass", (int)Inventory::tools["compass"]},
		{"Map", (int)Inventory::tools["map"]},
		{"Matches", (int)Inventory::tools["matches"]},
		{"Lens", (int)Inventory::tools["lens"]},
		{"Knife", (int)Inventory::tools["knife"]},
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
	rope = data["Rope"];
	Inventory::tools["axe"] = data["Axe"];
	Inventory::tools["flashlight"] = data["Flashlight"];
	Inventory::tools["lighter"] = data["Lighter"];
	Inventory::tools["fishing rod"] = data["FishingRod"];
	Inventory::tools["compass"] = data["Compass"];
	Inventory::tools["map"] = data["Map"];
	Inventory::tools["matches"] = data["Matches"];
	Inventory::tools["lens"] = data["Lens"];
	Inventory::tools["knife"] = data["Knife"];
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
	cout << "Rope = " << rope;
}

void Inventory::SetDeffaultCharacteristics()
{
	food = 1;
	water = 1;
	wood = 0;
	tinder = 0;
	medicine = 0;
	rope = 0;
	checkClickExploreArea = 0;

	Inventory::tools["axe"] = 1;
	Inventory::tools["flashlight"] = 0;
	Inventory::tools["lighter"] = 1;
	Inventory::tools["fishing rod"] = 1;
	Inventory::tools["compass"] = 0;
	Inventory::tools["map"] = 1;
	Inventory::tools["matches"] = 1;
	Inventory::tools["lens"] = 1;
	Inventory::tools["knife"] = 0;
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
	if (item_name == "rope")
		return rope;
}

void Inventory::DisplayInventory(sf::RenderWindow& window, sf::Vector2f windowResolution)
{
	sf::Font font;
	font.loadFromFile("CALIBRI.TTF");
	sf::Text Items, Items_Title, Items_Values, Tools, Tools_Title, Tools_Values;
	sf::Color textColor = sf::Color::Black;

	Items.setFont(font);
	Items_Title.setFont(font);
	Items_Values.setFont(font);
	Tools.setFont(font);
	Tools_Title.setFont(font);
	Tools_Values.setFont(font);

	Items_Title.setString("Items");
	Items.setString("Wood\nFood\nWater\nTinder\nMedicine\nRope");
	Items_Values.setString(to_string(Inventory::ReturnNumberOfItems("wood")) + "\n" +
		to_string(Inventory::ReturnNumberOfItems("food")) + "\n" +
		to_string(Inventory::ReturnNumberOfItems("water")) + "\n" +
		to_string(Inventory::ReturnNumberOfItems("tinder")) + "\n" +
		to_string(Inventory::ReturnNumberOfItems("medicine")) + "\n" +
		to_string(Inventory::ReturnNumberOfItems("rope")));
	Tools_Title.setString("Tools");
	Tools.setString("Axe\nFlashlight\nLighter\nFishing rod\nCompass\nMap\nMatches\nLens\nKnife\nSpear\nSpring trap\nBird trap\nFall trap");
	Tools_Values.setString(to_string(Inventory::Check_Tool("axe")) + "\n" +
		to_string(Inventory::Check_Tool("flashlight")) + "\n" +
		to_string(Inventory::Check_Tool("lighter")) + "\n" +
		to_string(Inventory::Check_Tool("fishing rod")) + "\n" +
		to_string(Inventory::Check_Tool("compass")) + "\n" +
		to_string(Inventory::Check_Tool("map")) + "\n" +
		to_string(Inventory::Check_Tool("matches")) + "\n" +
		to_string(Inventory::Check_Tool("lens")) + "\n" +
		to_string(Inventory::Check_Tool("knife")) + "\n" +
		to_string(Inventory::Check_Tool("spear")) + "\n" +
		to_string(Inventory::Check_Tool("spring trap")) + "\n" +
		to_string(Inventory::Check_Tool("bird trap")) + "\n" +
		to_string(Inventory::Check_Tool("fall trap")));

	Items_Title.setCharacterSize(windowResolution.y / 20);
	Items.setCharacterSize(windowResolution.y / 40);
	Items_Values.setCharacterSize(windowResolution.y / 40);
	Tools_Title.setCharacterSize(windowResolution.y / 20);
	Tools.setCharacterSize(windowResolution.y / 40);
	Tools_Values.setCharacterSize(windowResolution.y / 40);

	Items_Title.setPosition((float)windowResolution.x * 0.5, (float)windowResolution.y * 0.12);
	Items.setPosition((float)windowResolution.x * 0.5, (float)windowResolution.y * 0.21);
	Items_Values.setPosition((float)windowResolution.x * 0.6, (float)windowResolution.y * 0.21);
	Tools_Title.setPosition((float)windowResolution.x * 0.15, (float)windowResolution.y * 0.12);
	Tools.setPosition((float)windowResolution.x * 0.15, (float)windowResolution.y * 0.21);
	Tools_Values.setPosition((float)windowResolution.x * 0.27, (float)windowResolution.y * 0.21);

	Items_Title.setFillColor(textColor);
	Items.setFillColor(textColor);
	Items_Values.setFillColor(textColor);
	Tools_Title.setFillColor(textColor);
	Tools.setFillColor(textColor);
	Tools_Values.setFillColor(textColor);

	window.draw(Items_Title);
	window.draw(Items);
	window.draw(Items_Values);
	window.draw(Tools_Title);
	window.draw(Tools);
	window.draw(Tools_Values);
}