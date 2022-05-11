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

Panel::Panel(Vector2f position, float sizeX, float sizeY)
{
	this->size.x = sizeX;
	this->size.y = sizeY;

	this->sprite.setTexture(Game::defPanel);
	this->setPosition(position);
	sprite.scale(sizeX / Game::defPanel.getSize().x, sizeY / Game::defPanel.getSize().y);
}

Panel::Panel(std::string texturePath, Vector2f position, float sizeX, float sizeY)
{
	this->size.x = sizeX;
	this->size.y = sizeY;

	this->image.loadFromFile(texturePath);
	this->texture.loadFromImage(image, IntRect(sf::Vector2i(0, 0), (sf::Vector2i)image.getSize()));
	this->sprite.setTexture(this->texture);
	this->setPosition(position);
	sprite.scale(sizeX / image.getSize().x, sizeY / image.getSize().y);
}

Panel::Panel(std::string texturePath, Vector2f position, Vector2f size)
{
	this->size.x = size.x;
	this->size.y = size.y;

	this->image.loadFromFile(texturePath);
	this->texture.loadFromImage(image, IntRect(sf::Vector2i(0, 0), (sf::Vector2i)image.getSize()));
	this->sprite.setTexture(this->texture);
	this->setPosition(position);
	sprite.scale(size.x / image.getSize().x, size.y / image.getSize().y);
}

void Panel::setTexture(Texture* texture)
{
	this->sprite.setTexture(*texture);
}

void Panel::setSize(IntRect intRect)
{
	this->sprite.setTextureRect(intRect);
}

float Panel::getHeight()
{
	//return this->sprite.getLocalBounds().height;
	return size.y;
}

float Panel::getWidth()
{
	//return this->sprite.getLocalBounds().width;
	return size.x;
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