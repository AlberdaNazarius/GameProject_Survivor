#include "Label.h"

Label::Label(Vector2f pos, std::string text, int fontSize)
{
	this->relPosition = pos;
	this->text.setFont(Game::defFont);
	this->text.setString(text);
	this->text.setString(text);
	this->text.setCharacterSize(fontSize);
}

Label::Label(Vector2f pos, std::string text, int fontSize, Font* font)
{
	this->relPosition = pos;
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setString(text);
	this->text.setCharacterSize(fontSize);
}

void Label::render(RenderTarget& target, Vector2f offset)
{
	if (isVisible)
	{
		this->text.setPosition(offset + relPosition);
		target.draw(this->text);
	}
}