#include "Bar.h"

Bar::Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY)
{
	outlineImage.loadFromFile(outlineLocation);
	scaleImage.loadFromFile(scaleLocation);

	outlineTexture.loadFromImage(outlineImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)outlineImage.getSize()));
	scaleTexture.loadFromImage(scaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)scaleImage.getSize()));

	outlineSprite.setTexture(outlineTexture);
	scaleSprite.setTexture(scaleTexture);

	TextureAdaptation(sizeX, sizeY);
}

Bar::Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY, std::string text, Color color)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	outlineImage.loadFromFile(outlineLocation);
	scaleImage.loadFromFile(scaleLocation);

	outlineTexture.loadFromImage(outlineImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)outlineImage.getSize()));
	scaleTexture.loadFromImage(scaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)scaleImage.getSize()));

	outlineSprite.setTexture(outlineTexture);
	scaleSprite.setTexture(scaleTexture);
	TextureAdaptation(sizeX, sizeY);

	this->text.setFont(Game::defFont);
	this->text.setCharacterSize((sizeX + sizeY) / 11);
	this->text.setString(text);
	this->text.setFillColor(color);
}

void Bar::SetScale(float x)
{
	scaleSprite.setScale(sf::Vector2f(x / maxValue * adoptedScale.x, scaleSprite.getScale().y));
}

void Bar::SetScale(float x, float y)
{
	scaleSprite.setScale(sf::Vector2f(x / maxValue * adoptedScale.x, y / maxValue * adoptedScale.y));
}

void Bar::SetMaxValue(int maxValue) { this->maxValue = maxValue; }

void Bar::SetPosition(sf::Vector2f position)
{
	outlineSprite.setPosition(position);
	scaleSprite.setPosition(position);
	text.setPosition(position);
}

void Bar::SetPosition(int x, int y)
{
	outlineSprite.setPosition(x, y);
	scaleSprite.setPosition(x, y);
	if (text.getString() != "")
		text.setPosition(x + sizeX / 4, y + sizeY / 4);
}

void Bar::Render(sf::RenderWindow& window)
{
	window.draw(scaleSprite);
	window.draw(outlineSprite);
	window.draw(text);
}

void Bar::TextureAdaptation(float sizeX, float sizeY)
{
	float sizeCoefficient[2];

	sizeCoefficient[0] = outlineImage.getSize().x / sizeX;
	sizeCoefficient[1] = outlineImage.getSize().y / sizeY;
	outlineSprite.scale(1 / sizeCoefficient[0], 1 / sizeCoefficient[1]);

	sizeCoefficient[0] = scaleImage.getSize().x / sizeX;
	sizeCoefficient[1] = scaleImage.getSize().y / sizeY;
	scaleSprite.scale(1 / sizeCoefficient[0], 1 / sizeCoefficient[1]);
	adoptedScale = scaleSprite.getScale();
}