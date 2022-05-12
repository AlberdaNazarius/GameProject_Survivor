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

Bar::Bar(std::string outlineLocation, std::string scaleLocation, std::string backScale, float sizeX, float sizeY, std::string text, Color color)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	outlineImage.loadFromFile(outlineLocation);
	scaleImage.loadFromFile(scaleLocation);
	backScaleImage.loadFromFile(backScale);

	outlineTexture.loadFromImage(outlineImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)outlineImage.getSize()));
	scaleTexture.loadFromImage(scaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)scaleImage.getSize()));
	backScaleTexture.loadFromImage(backScaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)backScaleImage.getSize()));

	outlineSprite.setTexture(outlineTexture);
	scaleSprite.setTexture(scaleTexture);
	backScaleSprite.setTexture(backScaleTexture);
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
	backScaleSprite.setPosition(position);
	if (text.getString() != "")
		text.setPosition(position.x + sizeX / 4, position.y + sizeY / 4);
}

void Bar::SetPosition(int x, int y)
{
	outlineSprite.setPosition(x, y);
	scaleSprite.setPosition(x, y);
	backScaleSprite.setPosition(x, y);
	if (text.getString() != "")
		text.setPosition(x + sizeX / 4, y + sizeY / 4);
}

void Bar::Render(sf::RenderWindow& window)
{
	if (scaleSprite.getTexture() != NULL)
		window.draw(backScaleSprite);
	window.draw(scaleSprite);
	window.draw(outlineSprite);
	if (text.getString() != "")
		window.draw(text);
}

void Bar::TextureAdaptation(float sizeX, float sizeY)
{
	outlineSprite.scale(sizeX / outlineImage.getSize().x, sizeY / outlineImage.getSize().y);
	scaleSprite.scale(sizeX / scaleImage.getSize().x, sizeY / scaleImage.getSize().y);
	backScaleSprite.scale(sizeX / backScaleImage.getSize().x, sizeY / backScaleImage.getSize().y);

	adoptedScale = scaleSprite.getScale();
}