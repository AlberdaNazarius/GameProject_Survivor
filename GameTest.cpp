#include <SFML/Graphics.hpp>
#include <string>
#include "Location.h"

int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 720;
	Location location;
	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game"/*, sf::Style::Fullscreen */);
	location.SetWindowResolution(windowWidth, windowHeight);
	
	Forest* forest = new Forest();
	forest->Picture("Tiles/Environment.jpg");

	Lake* lake = new Lake();
	lake->Picture("Tiles/Lake.jpg");
	
	location.CheckWhatEnvironment((Environment*)forest);
	while (window.isOpen())
	{
		//window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close(); // need to save game

			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				location.CheckWhatEnvironment((Environment*)forest);
			else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
				location.CheckWhatEnvironment((Environment*)lake);
		}
		window.draw(location.Sprite);
		window.display();
	}
	return 0;
}