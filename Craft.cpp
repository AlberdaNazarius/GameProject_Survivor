#include "Craft.h"
#include "Character.h"

using namespace std;

map<string, map<string, int>> Craft::recipes = {      // map <craft item, map<ingredients, quantity> >
	{"spear", {    {"wood", 3 }, {"knife", 1 }    }},
	{"rope", {    {"tinder", 3 }    }},
	{"spring trap", {    {"wood", 1 }, {"rope", 2 }    }},
	{"bird trap", {    {"wood", 2 }    }},
	{"fall trap", {    {"wood", 4 }    }},
	{"fishing rod", {    {"wood", 2 }, {"rope", 1 }    }},
	{"shelter", {    {"tinder", 5 } ,{"wood", 5 }, {"rope", 3 }    }},
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
void Craft::InitializeCraftMenus(vector<Panel*>* craftMenus, map<Button<bool(*)(string)>*, string>* craftBut, map<Button<void(*)(vector<Panel*>*, Panel*)>*, Panel*>* switchBut, Container* mainCont, Vector2f windowResolution)
{
	const int colPerMenu = 8;
	Label* tempLabel;
	Button<bool(*)(string)>* tempBut;
	Button<void(*)(vector<Panel*>*, Panel*)>* tempSwiBut;
	Container* tempCont;
	string tempStr;
	int recQuant = Craft::recipesQuantity();
	for (int i = 0; ; i++)
	{
		if (i * colPerMenu >= recQuant)
		{
			return; 
		}
		(*craftMenus).push_back(new Panel(Vector2f(windowResolution.x / 10, windowResolution.y / 10), windowResolution.x * 0.8, windowResolution.y * 0.6));
		if (i != 0)   // next button delegate set
		{
			(*switchBut).insert({ tempSwiBut, (*craftMenus)[i] });
		}

		tempLabel = new Label(Vector2f(windowResolution.x * 0.38, windowResolution.y * 0.02), "Craft", windowResolution.y * 0.04);   // recipe name
		tempLabel->setColor(Color::Black);
		(*craftMenus)[i]->addChild(tempLabel);
		for (int j = 0; j < colPerMenu; j++)
		{
			if ((i * colPerMenu) + j >= recQuant)
			{
				break;
			}
			tempCont = new Container;  // single recipe container
			tempCont->setPosition(Vector2f(0, windowResolution.y * 0.13 + (windowResolution.y * 0.052 * j)));
			(*craftMenus)[i]->addChild(tempCont);

			tempStr = Craft::getRecipeName((i * colPerMenu) + j);
			tempLabel = new Label(Vector2f(windowResolution.x * 0.04, windowResolution.y * 0.02), tempStr, windowResolution.y * 0.025);   // recipe name
			tempLabel->setColor(Color::Black);
			tempCont->addChild(tempLabel);

			vector<string> tempStrVec = Craft::getRecipeIngs(tempStr);
			for (int k = 0; k < tempStrVec.size(); k++)
			{
				tempLabel = new Label(Vector2f(windowResolution.x * 0.2 + (windowResolution.x * 0.1 * (k + 1)), windowResolution.y * 0.02), tempStrVec[k], windowResolution.y * 0.025);   // recipe ingridient
				tempLabel->setColor(Color::Black);
				tempCont->addChild(tempLabel);
			}

			tempBut = new Button<bool(*)(string)>(Vector2f((windowResolution.x * 0.8) - (windowResolution.x * 0.1), windowResolution.y * 0.01), Vector2f(windowResolution.x * 0.06, windowResolution.y * 0.04), "Craft");
			tempBut->setDelegate(Craft::craftItem); // set delegate
			(*craftBut).insert({ tempBut, tempStr });
			tempCont->addChild(tempBut);
		}
		/*if (i != 0)
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
		}*/

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
		if (key[i] == "rope")
			if (Inventory::rope - (recipes[craftItem])[key[i]] > 0)
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
	//		Check if tool already exist
	if (recipes.find(craftItem) != recipes.end()) {
		if (Inventory::tools.find(craftItem) != Inventory::tools.end())
			if (Inventory::tools[craftItem])
				return false;
	}
	else
		return false;
	if (craftItem == "shelter" && Location::Shelter == true)
	{
		return false;
	}

	//		Check ingredients
	vector<string> key;
	for (map<string, int>::iterator it = recipes[craftItem].begin(); it != recipes[craftItem].end(); ++it)
		key.push_back(it->first);
	bool enough = true;
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] == "food")
			if (Inventory::food - (recipes[craftItem])[key[i]] >= 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "water")
			if (Inventory::water - (recipes[craftItem])[key[i]] >= 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "wood")
			if (Inventory::wood - (recipes[craftItem])[key[i]] >= 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "tinder")
			if (Inventory::tinder - (recipes[craftItem])[key[i]] >= 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "medicine")
			if (Inventory::medicine - (recipes[craftItem])[key[i]] >= 0)
				continue;
			else
			{
				enough = false;
				break;
			}
		if (key[i] == "rope")
			if (Inventory::rope - (recipes[craftItem])[key[i]] >= 0)
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

	//		Adding item and removing ingredients
	if (enough)
	{
		for (int i = 0; i < key.size(); i++)
		{
			if (key[i] == "food")
			{
				Inventory::food -= (recipes[craftItem])[key[i]];
			}
			if (key[i] == "water")
			{
				Inventory::water -= (recipes[craftItem])[key[i]];
			}
			if (key[i] == "wood")
			{
				Inventory::wood -= (recipes[craftItem])[key[i]];
			}
			if (key[i] == "tinder")
			{
				Inventory::tinder -= (recipes[craftItem])[key[i]];
			}
			if (key[i] == "medicine")
			{
				Inventory::medicine -= (recipes[craftItem])[key[i]];
			}
			if (key[i] == "rope")
				Inventory::rope -= (recipes[craftItem])[key[i]];
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
		if (craftItem == "rope")
			Inventory::rope += 1;
		if (craftItem == "shelter")
			Location::Shelter = true;
		if (Inventory::tools.find(craftItem) != Inventory::tools.end())
			Inventory::tools[craftItem] = true;
		GeneralTime::AddTime(0, 30);
		Character::DisplayCharacteristics();
		return true;
	}
	return false;
}