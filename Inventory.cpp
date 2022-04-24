#include "Inventory.h"

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