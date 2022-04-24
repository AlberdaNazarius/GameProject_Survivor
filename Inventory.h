#pragma once
#include <map>
#include <string>

using namespace std;

class Inventory
{
public:
	static void Change_Item(string item_name, int number);
	static int Show_Item(string item_name);
    static bool Check_Tool(string tool_id);
private:
	static int food, water, wood, tinder, medicine;
	static map<string, bool> tools;
};
