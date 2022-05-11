#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Container.h"
#include "Panel.h"
#include "Location.h"
#include <iostream>
using namespace sf;

class Menu
{
public:
	Menu();
	~Menu() {};
	void Draw();
	static bool OpenMainWindow() { return openMainWindow; }	
	static bool openMainWindow;	
	static RenderWindow MenuWindow;
private:
	Container* MenuContainer;
	Panel* MenuPanel;
	Container* OptionsContainer;
	Panel* OptionsPanel;
	Event event;
	Location location;
	Button<void(*)(bool)>* LoadSavedGame;
	Button<void(*)(bool)>* NewGame;
	Button<void(*)(Container*, Container*, bool)>* OpenOptions;
	Button<void(*)(RenderWindow&)>* Quit;
	Button<void(*)(Container*, Container*, bool)>* CloseOptions;
};

