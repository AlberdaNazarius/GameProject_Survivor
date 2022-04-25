#include "Inventory.h"
#include <ctime>
#include <iostream> // for testing

int  Inventory::food = 0,
Inventory::water = 0,
Inventory::wood = 0,
Inventory::tinder = 0,
Inventory::medicine = 0;

map<string, bool> Inventory::tools = {
		{"axe", false},
		{"flashlight", false},
		{"lighter", false},
		{"fishing rod", false},
		{"compass", false},
		{"map", false},
		{"matches", false},
		{"lens", false},
		{"knife", false},
		{"rope", false},
		{"spear", false},
};
bool Inventory::Check_Tool(string tool_id)
{
	return tools[tool_id];
}
void Inventory::ExploreArea()
{
	srand(time(NULL));
	for (auto iterator = tools.begin(); iterator != tools.end(); ++iterator)
	{
		tools[iterator->first] = rand() % 2;
		cout << iterator->first << " = " << tools[iterator->first] << endl; // test
	}
	food += rand() % 3; cout << "food = " << food << endl; // test
	water += rand() % 3; cout << "water = " << water << endl; // test
	wood += rand() % 3; cout << "wood = " << wood << endl; // test
	tinder += rand() % 3; cout << "tinder = " << tinder << endl; // test
	medicine += rand() % 3; cout << "medicine = " << medicine << endl; // test
}
