#pragma once
#include <SFML/Graphics.hpp>
#include "Container.h"
#include "Game.h"

using namespace sf;

class Panel : public Container
{
private:
	Sprite sprite;
public:
	Panel(Texture* texture, Vector2f pos, IntRect intRect);
	Panel(Vector2f pos, IntRect intRect);
	Panel();
	void setTexture(Texture* texture);
	void setSize(IntRect intRect);
	void render(RenderTarget& target, Vector2f offset);
};