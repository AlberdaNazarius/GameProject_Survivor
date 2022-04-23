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

using namespace sf;
using namespace std;

///* delete this after test
void testF()
{
	std::cout << "abcd";
}
//*/

int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 720;
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

	Button<void(*)()>* testButton = new Button<void(*)()>(Vector2f(400, 200), IntRect(0, 0, 128, 200), "ABC");
	testButton->setDelegate(testF);      // test


	Button<void(*) (int)>* stayAtFire = new Button<void(*) (int)>(Vector2f(40, 40), IntRect(0, 0, 200, 100), "Stay st fire");
	stayAtFire->setDelegate(Character::ChangeWarmthLevel);
	

	Container* uiContainer = new Container;
	Panel* testPanel = new Panel(Vector2f(300,100), IntRect(0, 0, 640, 480));

	uiContainer->addChild(testPanel);


	testPanel->addChild(testButton);
	testPanel->addChild(stayAtFire);
	
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
					if (stayAtFire->checkClick((Vector2f)Mouse::getPosition(window))) stayAtFire->Action(10); 
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
		stayAtFire->update((Vector2f)Mouse::getPosition(window)); 

		// Draw
		window.clear();
		window.draw(location.Sprite);

		uiContainer->render(window, Vector2f(0, 0));    // render themself and all ui that contain
		window.display();
	}

	// Deleteing dynamic objects

	return 0;
}