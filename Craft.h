#pragma once
#include <string>
#include <map>
#include <vector>
#include "Inventory.h"
#include "Location.h"
#include "Button.h"
#include "Container.h"
#include "Panel.h"
#include "Label.h"

using namespace std;

class Craft
{
public:
	static bool canCraft(string craftItem);
	static bool craftItem(string craftItem);
	static int recipesQuantity();
	static string getRecipeName(int index);
	static vector<string> getRecipeIngs(string craftItem);
	static void changeCraftMenu(vector<Panel*>* craftMenus, Panel* newCraftMenu);
	static void InitializeCraftMenus(vector<Panel*>* craftMenus, map<Button<bool(*)(string)>*, string>* craftBut, map<Button<void(*)(vector<Panel*>*, Panel*)>*, Panel*>* switchBut, Container* mainCont, Vector2f craftMenuPos);
private:
	static map<string, map<string, int>> recipes;
};