#include "Craft.h"
#include "Character.h"

using namespace std;

map<string, map<string, int>> Craft::recipes = {      // map <craft item, map<ingredients, quantity> >
	{"spear", {    {"wood", 20 }, {"knife", 1 }    }},
	{"rope", {    {"tinder", 20 }    }},
	{"spring trap", {    {"wood", 15 }, {"rope", 1 }    }},
	{"bird trap", {    {"wood", 20 }    }},
	{"fall trap", {    {"wood", 30 }    }},
	{"fishing rod", {    {"wood", 10 }, {"rope", 1 }    }},
};

int Craft::recipesQuantity()
{
	return recipes.size();
}

string Craft::getRecipeName(int index)
{
	int i = 0;
	for (map<string, map<string, int>>::iterator it = recipes.begin(); it != recipes.end(); ++it)
	{
		if (i == index)
		{
			return it->first;
		}
		i++;
	}
	return "";
}

vector<string> Craft::getRecipeIngs(string craftItem)
{
	vector<string> key;
	for (map<string, int>::iterator it = recipes[craftItem].begin(); it != recipes[craftItem].end(); ++it)
	{
		key.push_back(it->first);
		key.back() += " ";
		key.back() += to_string(it->second);
	}
	return key;
}

void Craft::changeCraftMenu(vector<Panel*>* craftMenus, Panel* newCraftMenu)
{
	for (int i = 0; i < (*craftMenus).size(); i++)
	{
		(*craftMenus)[i]->setVisible(false);
	}
	if (newCraftMenu != NULL)
	{
		newCraftMenu->setVisible(true);
	}
}
void Craft::InitializeCraftMenus(vector<Panel*>* craftMenus, map<Button<bool(*)(string)>*, string>* craftBut, vector<Button<void(*)(vector<Panel*>*, Panel*)>*>* closeBut, map<Button<void(*)(vector<Panel*>*, Panel*)>*, Panel*>* switchBut, Container* mainCont, Vector2f craftMenuPos)
{
	const int colPerMenu = 8;
	Label* tempLabel;
	Button<bool(*)(string)>* tempBut;
	Button<void(*)(vector<Panel*>*, Panel*)>* tempSwiBut;
	string tempStr;
	int recQuant = Craft::recipesQuantity();
	for (int i = 0; ; i++)
	{
		if (i * colPerMenu >= recQuant)
		{
			return; 
		}
		(*craftMenus).push_back(new Panel(craftMenuPos, (float)VideoMode::getDesktopMode().width * 0.8, (float)VideoMode::getDesktopMode().height * 0.6));
		if (i != 0)   // next button delegate set
		{
			(*switchBut).insert({ tempSwiBut, (*craftMenus)[i] });
		}
		tempSwiBut = new Button<void(*)(vector<Panel*>*, Panel*)>(Vector2f(550, 0), Vector2f(90, 32), "Exit");
		tempSwiBut->setDelegate(changeCraftMenu); // set delegate
		(*closeBut).push_back(tempSwiBut);
		(*craftMenus)[i]->addChild(tempSwiBut);
		for (int j = 0; j < colPerMenu; j++)
		{
			if ((i * colPerMenu) + j >= recQuant)
			{
				break;
			}
			tempStr = Craft::getRecipeName((i * colPerMenu) + j);
			tempLabel = new Label(Vector2f(20, 40 + (40 * j)), tempStr, 14);   // recipe name
			(*craftMenus)[i]->addChild(tempLabel);
			vector<string> tempStrVec = Craft::getRecipeIngs(tempStr);
			for (int k = 0; k < tempStrVec.size(); k++)
			{
				tempLabel = new Label(Vector2f(20 + (100 * (k + 1)), 40 + (40 * j)), tempStrVec[k], 14);   // recipe name
				(*craftMenus)[i]->addChild(tempLabel);
			}
			tempBut = new Button<bool(*)(string)>(Vector2f(20 + (100 * (tempStrVec.size() + 1)), 40 + (40 * j) - 8), Vector2f(90, 32), "Craft");
			tempBut->setDelegate(Craft::craftItem); // set delegate
			(*craftBut).insert({ tempBut, tempStr });
			(*craftMenus)[i]->addChild(tempBut);
		}
		if (i != 0)
		{
			tempSwiBut = new Button<void(*)(vector<Panel*>*, Panel*)>(Vector2f(330, 448), Vector2f(90, 32), "Previous");
			tempSwiBut->setDelegate(changeCraftMenu); // set delegate
			(*switchBut).insert({ tempSwiBut, (*craftMenus)[i - 1] });
			(*craftMenus)[i]->addChild(tempSwiBut);
		}

		if ((i + 1) * colPerMenu < recQuant)
		{
			tempSwiBut = new Button<void(*)(vector<Panel*>*, Panel*)>(Vector2f(220, 448), Vector2f(90, 32), "Next");
			tempSwiBut->setDelegate(changeCraftMenu); // set delegate
			(*craftMenus)[i]->addChild(tempSwiBut);
		}

		mainCont->addChild((*craftMenus)[i]);
		(*craftMenus)[i]->setVisible(false);
	}
}

bool Craft::canCraft(string craftItem)
{
	vector<string> key;
	for (map<string, int>::iterator it = recipes[craftItem].begin(); it != recipes[craftItem].end(); ++it)
		key.push_back(it->first);
	bool enough = true;
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] == "food")
			if (Inventory::food - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "water")
			if (Inventory::water - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "wood")
			if (Inventory::wood - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "tinder")
			if (Inventory::tinder - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "medicine")
			if (Inventory::medicine - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		enough = Inventory::tools[key[i]];
		if (!enough)
			break;
	}
	return enough;
}

bool Craft::craftItem(string craftItem)
{
	if (recipes.find(craftItem) != recipes.end()) {
		if (Inventory::tools.find(craftItem) != Inventory::tools.end())
		{
			if (Inventory::tools[craftItem])
			{
				return false;
			}
		}
	}
	else
		return false;
	vector<string> key;
	for (map<string, int>::iterator it = recipes[craftItem].begin(); it != recipes[craftItem].end(); ++it)
		key.push_back(it->first);
	bool enough = true;
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] == "food")
			if (Inventory::food - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "water")
			if (Inventory::water - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "wood")
			if (Inventory::wood - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "tinder")
			if (Inventory::tinder - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "medicine")
			if (Inventory::medicine - (recipes[craftItem])[key[i]] > 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		enough = Inventory::tools[key[i]];
		if (!enough)
			break;
	}
	if (enough)
	{
		for (int i = 0; i < key.size(); i++)
		{
			if (key[i] == "food")
				Inventory::food -= (recipes[craftItem])[key[i]];
			if (key[i] == "water")
				Inventory::water -= (recipes[craftItem])[key[i]];
			if (key[i] == "wood")
				Inventory::wood -= (recipes[craftItem])[key[i]];
			if (key[i] == "tinder")
				Inventory::tinder -= (recipes[craftItem])[key[i]];
			if (key[i] == "medicine")
				Inventory::medicine -= (recipes[craftItem])[key[i]];
		}
		if (craftItem == "food")
			Inventory::food += 10;
		if (craftItem == "water")
			Inventory::water += 10;
		if (craftItem == "wood")
			Inventory::wood += 10;
		if (craftItem == "tinder")
			Inventory::tinder += 20;
		if (craftItem == "medicine")
			Inventory::medicine += 5;
		Inventory::tools[craftItem] = true;
		GeneralTime::AddTime(0, 30);
		Character::DisplayCharacteristics();
		return true;
	}
	return false;
}