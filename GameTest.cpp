#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Location.h"
#include "Game.h"
#include "Button.h"
#include "Data.h"
#include "Character.h"
#include "UI.h"
#include "Container.h"
#include "Panel.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

///* delete this after test
void testF()
{
	std::cout << "abcd";
}
//*/

#pragma region StartFire

template <typename T>
void ButtonSetVisible(Button<T>* button, bool value)
{
	button->setVisible(value);
}
void ContainerSetVisible(Container*  cont, bool value)
{
	cont->setVisible(value);
}

#pragma endregion

int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 920;
	RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game"/*, sf::Style::Fullscreen */);
	Event event;
	Location location;
	location.SetWindowResolution(windowWidth, windowHeight);

	Game::errorTexture.setRepeated(true);
	if (!Game::errorTexture.loadFromFile("Pictures/ErrorTexture.png"))
		throw std::invalid_argument("Failed to load ErrorTexture.png");
	if (!Game::defFont.loadFromFile("Fonts/Roboto-Regular.ttf"))
		throw std::invalid_argument("Failed to load Roboto-Light.ttf");
	Game::defIdleBut = Game::errorTexture;
	Game::defClickedBut = Game::errorTexture;
	Game::defHoverBut = Game::errorTexture;
	if (!Game::defPanel.loadFromFile("Pictures/DefaultPanel.png"))
	{
		Game::defPanel = Game::errorTexture;
		Game::defPanel.setRepeated(true);
	}
	
#pragma region StartFire

	Container* StartFireContainer = new Container;
	Panel* StartFirePanel = new Panel(Vector2f(100, 490), IntRect(0, 0, 1040, 380));
	StartFireContainer->setVisible(false);

	Button<void(*)(Container*, bool)>* StartFire = new Button<void(*)(Container*, bool)>(Vector2f(40, 40), IntRect(0, 0, 200, 100), "Start fire");
	StartFire->setDelegate(ContainerSetVisible);

	Button<void(*)(int)>* StayAtFire = new Button<void(*)(int)>(Vector2f(260, 40), IntRect(0, 0, 200, 100), "Stay at fire");
	StayAtFire->setDelegate(Character::ChangeWarmthLevel);
	StayAtFire->setVisible(false);
	int startedHour = 0;

	Button<void(*)(Button<void(*)(int)>*, bool)>* FireLighter = new Button< void(*)(Button<void(*)(int)>*, bool) >(Vector2f(10, 10), IntRect(0, 0, 150, 100), "Lighter");
	FireLighter->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, bool)>* FireStone = new Button<void(*)(Button<void(*)(int)>*, bool)>(Vector2f(170, 10), IntRect(0, 0, 150, 100), "Flint and Stone");
	FireStone->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, bool)>* FireMatches = new Button<void(*)(Button<void(*)(int)>*, bool)>(Vector2f(340, 10), IntRect(0, 0, 150, 100), "Matches");
	FireMatches->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, bool)>* FireBow = new Button<void(*)(Button<void(*)(int)>*, bool)>(Vector2f(490, 10), IntRect(0, 0, 150, 100), "Bow method");
	FireBow->setDelegate(ButtonSetVisible);

	Button<void(*)(Button<void(*)(int)>*, bool)>* FireLens = new Button<void(*)(Button<void(*)(int)>*, bool)>(Vector2f(660, 510), IntRect(0, 0, 150, 100), "Lens");
	FireLens->setDelegate(ButtonSetVisible);

	StartFireContainer->addChild(StartFirePanel);

	StartFirePanel->addChild(FireStone);
	StartFirePanel->addChild(FireBow);
    StartFirePanel->addChild(FireLighter);
	StartFirePanel->addChild(FireLens);
	StartFirePanel->addChild(FireMatches);

	if (!Inventory::Check_Tool("lighter")) FireLighter->setVisible(false);
	if (!Inventory::Check_Tool("lens")) FireLens->setVisible(false);
	if (!Inventory::Check_Tool("matches")) FireMatches->setVisible(false);

#pragma endregion 

	Button<void(*)()>* testButton = new Button<void(*)()>(Vector2f(400, 200), IntRect(0, 0, 128, 200), "ABC");
	testButton->setDelegate(testF);      // test

	Container* uiContainer = new Container;
	Panel* testPanel = new Panel(Vector2f(300,10), IntRect(0, 0, 640, 480));

	uiContainer->addChild(testPanel);

	testPanel->addChild(testButton);
	testPanel->addChild(StayAtFire);
	testPanel->addChild(StartFire);
	
	// Attaching pictures to environments
	Forest::SetPicture("Pictures/Environment.jpg");
	Lake::SetPicture("Pictures/Lake.jpg");
	
	//Main cycle
	while (window.isOpen())
	{
		// Event
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close(); // need to save game here
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (testButton->checkClick((Vector2f)Mouse::getPosition(window))) testButton->Action();
#pragma region StartFire
					if (StartFire->checkClick((Vector2f)Mouse::getPosition(window)))
					{
						StartFire->Action(StartFireContainer, !StartFireContainer->getVisible());
						startedHour = GeneralTime::GetHours();
					}
					if (FireLighter->checkClick((Vector2f)Mouse::getPosition(window)))  FireLighter->Action(StayAtFire, true);
					if (FireStone->checkClick((Vector2f)Mouse::getPosition(window)))  FireStone->Action(StayAtFire, true);
					if (FireMatches->checkClick((Vector2f)Mouse::getPosition(window)))  FireMatches->Action(StayAtFire, true);
					if (FireBow->checkClick((Vector2f)Mouse::getPosition(window)))  FireBow->Action(StayAtFire, true);
					if (FireLens->checkClick((Vector2f)Mouse::getPosition(window)))  FireLens->Action(StayAtFire, true);
					if (StayAtFire->checkClick((Vector2f)Mouse::getPosition(window))) StayAtFire->Action(10);
#pragma endregion 
				}
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::A:
					uiContainer->setVisible(!uiContainer->getVisible());	// test
					break;
				case Keyboard::B:
					testButton->setVisible(!testButton->getVisible());		// test
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel);
			else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel);
		}
		// Update
		testButton->update((Vector2f)Mouse::getPosition(window));

#pragma region StartFire

		FireLighter->update((Vector2f)Mouse::getPosition(window));
		FireBow->update((Vector2f)Mouse::getPosition(window));
		FireMatches->update((Vector2f)Mouse::getPosition(window));
		FireLens->update((Vector2f)Mouse::getPosition(window));
		FireStone->update((Vector2f)Mouse::getPosition(window));
		StayAtFire->update((Vector2f)Mouse::getPosition(window));
	 	StartFire->update((Vector2f)Mouse::getPosition(window));
#pragma endregion 

		// Draw
		window.clear();
		window.draw(location.Sprite);
#pragma region StartFire
		if (GeneralTime::DeltaTime(0, startedHour) == 5) StayAtFire->setVisible(false); // an example; it's not necessary must be 5
		StartFireContainer->render(window, Vector2f(0, 0));
#pragma endregion 
		uiContainer->render(window, Vector2f(0, 0)); // render themself and all ui that contain
		window.display();
	}

	// Deleteing dynamic objects

	return 0;
}