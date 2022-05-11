#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"
using namespace sf;

class Bar
{
public:
	Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY);
	Bar(std::string outlineLocation, std::string scaleLocation, float sizeX, float sizeY, std::string text, Color color);

	void SetScale(float x);
	void SetScale(float x, float y);
	void SetMaxValue(int maxValue);
	void SetPosition(sf::Vector2f position);
	void SetPosition(int x, int y);
	void Render(sf::RenderWindow& window);

private:
	int sizeX, sizeY;
	float maxValue = 100;
	Image outlineImage;
	Image scaleImage;
	Texture outlineTexture;
	Texture scaleTexture;
	Sprite outlineSprite;
	Sprite scaleSprite;
	Vector2f adoptedScale;
	Text text;
	void TextureAdaptation(float sizeX, float sizeY);
};