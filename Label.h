#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"
#include "UI.h"
#include "Location.h"

using namespace sf;

class Label : public UI
{
private:
	Text text;
public:
	Label(Vector2f pos, std::string text, int fontSize);
	Label(Vector2f pos, std::string text, int fontSize, Color color);
	Label(Vector2f pos, std::string text, int fontSize, Font* font);
	void setText(std::string text);
	void setText(int text);
	void setColor(Color color);
	void render(RenderTarget& target, Vector2f offset);
};