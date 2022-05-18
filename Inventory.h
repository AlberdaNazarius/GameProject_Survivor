#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Interfaces.h"

using namespace std;

class Inventory : public IData
{
public:
	static void Change_Item(string item_name, int number);
    static bool Check_Tool(string tool_id);
	static string ExploreArea(int counterClick);
	static string LoseInventory();
	static void DisplayCharacteristics();
	static int ReturnNumberOfItems(string item_name);
	static void DisplayInventory(sf::RenderWindow& window, sf::Vector2f windowResolution);

	void ReloadData(map<std::string, int> data) override;
	void DisplayStats() override;
	void SetDeffaultCharacteristics() override;
	std::map<std::string, int> WhatToSave() override;

	static int food, water, wood, tinder, medicine, rope;
	static map<string, bool> tools;
	static int checkClickExploreArea;
};
