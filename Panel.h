#pragma once
#include <SFML/Graphics.hpp>
#include "Container.h"
#include "Game.h"

using namespace sf;

class Panel : public Container
{
private:
	Sprite sprite;
	Texture texture;
	Image image;
	Vector2f size;
public:
	Panel();
	Panel(Texture* texture, Vector2f pos, IntRect intRect);
	Panel(Vector2f pos, IntRect intRect);

	Panel(Vector2f position, float sizeX, float sizeY);
	Panel(std::string texturePath, Vector2f position, float sizeX, float sizeY);
	Panel(std::string texturePath, Vector2f position, Vector2f size);

	void setTexture(Texture* texture);
	void setSize(IntRect intRect);

	float getHeight();
	float getWidth();

	void render(RenderTarget& target, Vector2f offset);
};