#pragma once
#include "SFML/Graphics.hpp"
#include "Panel.h"
#include "Location.h"
#include <iostream>
using namespace sf;

class Menu
{
public:
	Menu();
	~Menu();
	void Draw();
	static bool OpenMainWindow() { return openMainWindow; }
	static bool openMainWindow;
	static RenderWindow MenuWindow;
private:
	const int windowWidth = VideoMode::getDesktopMode().width;
	const int windowHeight = VideoMode::getDesktopMode().height;
	Container* MenuContainer;
	Panel* MenuPanel;
	Event event;
	Location location;
	Button<void(*)(bool)>* LoadSavedGame;
	Button<void(*)(bool)>* NewGame;
	Button<void(*)(RenderWindow&)>* Quit;
};

