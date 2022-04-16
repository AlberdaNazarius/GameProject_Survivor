#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::Sprite sprite;
	sf::Texture* idle;
	sf::Texture* clicked;
	sf::Texture* hover;
	sf::Font* font;
	sf::Text text;
	void (*pFunc)();
public:
	Button(sf::Vector2f pos, sf::IntRect intRect, std::string text);
	~Button();

	void setPosition(sf::Vector2f pos);

	void setSize(sf::IntRect intRect);

	void setTexture(sf::Texture* idle, sf::Texture* clicked);

	void setFont(sf::Font* font);

	void setDelegate(void (*func)());

	void update(sf::Vector2f pos);

	bool checkClick(sf::Vector2f pos);

	void render(sf::RenderTarget& target);
};