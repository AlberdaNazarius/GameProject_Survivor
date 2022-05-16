#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>
using namespace sf;

class Bar
{
public:
	Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY);
	Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY, std::string text, Color color);
	Bar(std::string outlineLocation, std::string scaleLocation, std::string backScaleLocation, float sizeX, float sizeY, std::string text, Color color);
	Bar(std::string outlineLocation, std::string scaleLocation, std::string backScaleLocation, float sizeX, float sizeY, int text, Color color);
	Bar(std::string outlineLocation, std::string scaleLocation, std::string backScaleLocation, std::string icoLocation, float sizeX, float sizeY, std::string text, Color color);

	void SetScale(float x);
	void SetScale(float x, float y);
	void SetIcoScale(float x, float y);
	void SetMaxValue(int maxValue);
	void SetPosition(sf::Vector2f position);
	void SetPosition(int x, int y);
	void SetText(int text);
	void SetTextAndScale(float value);

	void Render(sf::RenderWindow& window);

private:
	float sizeX, sizeY;
	float maxValue = 100;

	Image outlineImage;
	Image scaleImage;
	Image backScaleImage;
	Image icoImage;

	Texture outlineTexture;
	Texture scaleTexture;
	Texture backScaleTexture;
	Texture icoTexture;

	Sprite outlineSprite;
	Sprite scaleSprite;
	Sprite backScaleSprite;
	Sprite icoSprite;

	Text text;
	Vector2f adoptedScale;
	void TextureAdaptation(float sizeX, float sizeY);
};

class TemperatureBar
{
public:
	TemperatureBar(std::string hotTemperatureLocation, std::string coldTemperatureLocation, const float sizeX, const float sizeY, std::string text, Color color);

	void SetPosition(const float sizeX, const float sizeY);

	void ChangeTemperaturePicture(int temperature);
	void Render(sf::RenderWindow& window);
private:
	Image hotTemperatureImage;
	Image coldTemperatureImage;

	Texture hotTemperatureTexture;
	Texture coldTemperatureTexture;

	Sprite temperatureSprite;
	Text text;
};