#include "Bar.h"

Bar::Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY)
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

Bar::Bar(std::string outlineLocation, std::string scaleLocation, std::string backScaleLocation, float sizeX, float sizeY, std::string text, Color color)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	outlineImage.loadFromFile(outlineLocation);
	scaleImage.loadFromFile(scaleLocation);
	backScaleImage.loadFromFile(backScaleLocation);

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

Bar::Bar(std::string outlineLocation, std::string scaleLocation, std::string backScaleLocation, std::string icoLocation, float sizeX, float sizeY, std::string text, Color color)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	outlineImage.loadFromFile(outlineLocation);
	scaleImage.loadFromFile(scaleLocation);
	backScaleImage.loadFromFile(backScaleLocation);
	icoImage.loadFromFile(icoLocation);

	outlineTexture.loadFromImage(outlineImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)outlineImage.getSize()));
	scaleTexture.loadFromImage(scaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)scaleImage.getSize()));
	backScaleTexture.loadFromImage(backScaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)backScaleImage.getSize()));
	icoTexture.loadFromImage(icoImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)icoImage.getSize()));

	outlineSprite.setTexture(outlineTexture);
	scaleSprite.setTexture(scaleTexture);
	backScaleSprite.setTexture(backScaleTexture);
	icoSprite.setTexture(icoTexture);
	TextureAdaptation(sizeX, sizeY);

	this->text.setFont(Game::defFont);
	this->text.setCharacterSize((sizeX + sizeY) / 11);
	this->text.setString(text);
	this->text.setFillColor(color);
}

Bar::Bar(std::string outlineLocation, std::string scaleLocation, std::string backScaleLocation, float sizeX, float sizeY, int intText, Color color)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	outlineImage.loadFromFile(outlineLocation);
	scaleImage.loadFromFile(scaleLocation);
	backScaleImage.loadFromFile(backScaleLocation);

	outlineTexture.loadFromImage(outlineImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)outlineImage.getSize()));
	scaleTexture.loadFromImage(scaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)scaleImage.getSize()));
	backScaleTexture.loadFromImage(backScaleImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)backScaleImage.getSize()));

	outlineSprite.setTexture(outlineTexture);
	scaleSprite.setTexture(scaleTexture);
	backScaleSprite.setTexture(backScaleTexture);
	TextureAdaptation(sizeX, sizeY);

	std::string text = std::to_string(intText);
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

void Bar::SetIcoScale(float x, float y)
{
	icoSprite.setScale(x / icoImage.getSize().x, icoSprite.getScale().y);
}

void Bar::SetText(int text)
{
	this->text.setString(std::to_string(text));
}

void Bar::SetTextAndScale(float value)
{
	scaleSprite.setScale(sf::Vector2f(value / maxValue * adoptedScale.x, scaleSprite.getScale().y));
	this->text.setString(std::to_string((int)value));
}

void Bar::SetMaxValue(int maxValue) { this->maxValue = maxValue; }

void Bar::SetPosition(sf::Vector2f position)
{
	outlineSprite.setPosition(position);
	scaleSprite.setPosition(position);
	backScaleSprite.setPosition(position);
	icoSprite.setPosition(position);
	if (text.getString() != "")
		text.setPosition(position.x + sizeX / 2, position.y + sizeY / 4);
}

void Bar::SetPosition(int x, int y)
{
	outlineSprite.setPosition(x, y);
	scaleSprite.setPosition(x, y);
	backScaleSprite.setPosition(x, y);
	icoSprite.setPosition(x, y + sizeY/4);
	if (text.getString() != "")
		text.setPosition(x + sizeX / 2, y + sizeY / 4);
}

void Bar::Render(sf::RenderWindow& window)
{
	if (backScaleSprite.getTexture() != NULL)
		window.draw(backScaleSprite);
	window.draw(scaleSprite);
	window.draw(outlineSprite);
	if (icoSprite.getTexture() != NULL)
		window.draw(icoSprite);
	if (text.getString() != "")
		window.draw(text);
}

void Bar::TextureAdaptation(float sizeX, float sizeY)
{
	outlineSprite.scale(sizeX / outlineImage.getSize().x, sizeY / outlineImage.getSize().y);
	scaleSprite.scale(sizeX / scaleImage.getSize().x, sizeY / scaleImage.getSize().y);
	backScaleSprite.scale(sizeX / backScaleImage.getSize().x, sizeY / backScaleImage.getSize().y);
	icoSprite.scale(sizeX / icoImage.getSize().x, 0.9 * sizeY / icoImage.getSize().y);

	adoptedScale = scaleSprite.getScale();
}


// Other class
TemperatureBar::TemperatureBar(std::string hotTemperatureLocation, std::string coldTemperatureLocation, const float sizeX, const float sizeY, std::string text, Color color)
{
	hotTemperatureImage.loadFromFile(hotTemperatureLocation);
	coldTemperatureImage.loadFromFile(coldTemperatureLocation);

	hotTemperatureTexture.loadFromImage(hotTemperatureImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)hotTemperatureImage.getSize()));
	coldTemperatureTexture.loadFromImage(coldTemperatureImage, sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)coldTemperatureImage.getSize()));

	temperatureSprite.scale(sizeX / hotTemperatureImage.getSize().x, sizeY / hotTemperatureImage.getSize().y);

	this->text.setFont(Game::defFont);
	this->text.setCharacterSize((sizeX + sizeY) / 4);
	this->text.setString(text);
	this->text.setFillColor(color);
}

void TemperatureBar::SetPosition(const float x, const float y)
{
	text.setPosition(x, y);
	temperatureSprite.setPosition(x + 60, y / 2);
}

void TemperatureBar::ChangeTemperaturePicture(int temperature)
{
	if (temperature > 0)
		temperatureSprite.setTexture(hotTemperatureTexture);
	else
		temperatureSprite.setTexture(coldTemperatureTexture);
}

void TemperatureBar::Render(sf::RenderWindow& window)
{
	window.draw(temperatureSprite);
	window.draw(text);
}