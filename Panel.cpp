#include "Panel.h"

Panel::Panel(Texture* texture, Vector2f pos, IntRect intRect)
{
	this->sprite.setTexture(*texture);
	this->setPosition(pos);
	this->sprite.setTextureRect(intRect);
}

Panel::Panel(Vector2f pos, IntRect intRect)
{
	this->sprite.setTexture(Game::defPanel);
	this->setPosition(pos);
	this->sprite.setTextureRect(intRect);
}

Panel::Panel()
{
	this->sprite.setTexture(Game::defPanel);
}

void Panel::setTexture(Texture* texture)
{
	this->sprite.setTexture(*texture);
}

void Panel::setSize(IntRect intRect)
{
	this->sprite.setTextureRect(intRect);
}

void Panel::render(RenderTarget& target, Vector2f offset)
{

	if (isVisible)
	{
		this->sprite.setPosition(offset + relPosition);
		target.draw(this->sprite);
		for (int i = 0; i < this->childs.size(); i++)
			this->childs[i]->render(target, offset + relPosition);
	}
}