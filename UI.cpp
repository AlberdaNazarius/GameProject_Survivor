#include <SFML/Graphics.hpp>
#include "UI.h"

UI::UI(Vector2f pos, bool isVis)
{
	this->relPosition = pos;
	this->isVisible = isVis;
}

UI::UI(Vector2f pos)
{
	this->relPosition = pos;
}

UI::UI()
{
	this->relPosition = Vector2f(0, 0);
}

UI::~UI()
{
}

void UI::setPosition(Vector2f pos)
{
	this->relPosition = pos;
}

Vector2f UI::getPosition()
{
	return this->relPosition;
}

void UI::setVisible(bool isVis)
{
	this->isVisible = isVis;
}

bool UI::getVisible()
{
	return this->isVisible;
}

void UI::setActive(bool isAct)
{
	this->isActive = isAct;
}

bool UI::getActive()
{
	return this->isActive;
}

#pragma region SpriteWithText
SpriteWithText::SpriteWithText(std::string imageLocation, std::string text, Color color, Vector2f size)
{
	this->size = size;
	
	this->text.setFont(Game::defFont);
	this->text.setCharacterSize((size.x + size.y) / 3.5);
	this->text.setString(text);
	this->text.setFillColor(color);

	image.loadFromFile(imageLocation);
	texture.loadFromImage(image, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)image.getSize()));
	sprite.setTexture(texture);
	sprite.scale(size.x / image.getSize().x, size.y / image.getSize().y);
}

void SpriteWithText::SetPosition(float x, float y)
{
	this->position = Vector2f(x, y);
	text.setPosition(x, y + size.y / 4);
	sprite.setPosition(x + text.getLocalBounds().width + text.getLocalBounds().width / 4, y);
}

void SpriteWithText::SetPosition(Vector2f position)
{
	this->position = position;
	text.setPosition(position.x, position.y + size.y / 4);
	sprite.setPosition(position.x + text.getLocalBounds().width + text.getLocalBounds().width / 4, position.y);
}

void SpriteWithText::SetTextSize(int characterSize)
{
	text.setCharacterSize(characterSize);
}

void SpriteWithText::SetTexPosition(Vector2f position)
{
	text.setPosition(position);
}

void SpriteWithText::SetText(std::string text)
{
	this->text.setString(text);
}

Vector2f SpriteWithText::GetPosition()
{
	return position;
}

Vector2f SpriteWithText::GetTextPosition()
{
	return text.getPosition(); 
}

void SpriteWithText::SetDistanceBetweenObjects(Vector2f distance, SpriteWithText* object, int amount)
{
	for (int i = 0; i < amount; i++)
		object[i].SetPosition(position.x + i * distance.x, position.y + i * distance.y);
}

void SpriteWithText::Render(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(text);
}
#pragma endregion
