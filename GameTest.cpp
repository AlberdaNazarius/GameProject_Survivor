#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Location.h"
#include "Game.h"
#include "Button.h"
#include "Data.h"

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

	Button testButton(Vector2f(600, 200), IntRect(0, 0, 128, 200), "ABC");
	testButton.setDelegate(testF);      // test
	
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
					testButton.checkClick((Vector2f)Mouse::getPosition(window));
				}
				break;
			default:
				break;
			}
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel);
			else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel);
		}
		// Update
		testButton.update((Vector2f)Mouse::getPosition(window));

		// Draw
		//window.clear(sf::Color::Black);
		window.clear();
		window.draw(location.Sprite);
		testButton.render(window);
		window.display();
	}

	// Deleteing dynamic objects

	return 0;
}