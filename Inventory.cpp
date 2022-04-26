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
		{"fishing rod", false},
		{"compass", false},
		{"map", true},
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
	srand(time(0));
	tools["matches"] = rand() % 2;
	tools["flashlight"] = rand() % 2;
	food += rand() % 3; cout << "food = " << food << endl; // test
	water += rand() % 3; cout << "water = " << water << endl; // test
	wood += rand() % 3; cout << "wood = " << wood << endl; // test
	tinder += rand() % 3; cout << "tinder = " << tinder << endl; // test
	medicine += rand() % 3; cout << "medicine = " << medicine << endl; // test
	Character::ChangeEnergyLevel(-15);
	Generator::GenerateEnvironments(2, 3);
}
