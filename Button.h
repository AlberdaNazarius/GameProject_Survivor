#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"
#include <iostream>
using namespace sf;

template<typename T>
class Button : public UI
{
private:
	Sprite sprite;
	Texture uniqueTexture;
	Texture* idle;
	Texture* clicked;
	Texture* hover;
	Image image;
	Font* font;
	Text text;
	Vector2f size;
	Vector2f position;
	bool contains;
	bool  renderText = true;
public:
        T Action;
		Button(Vector2f pos, IntRect intRect, std::string text)
		{
				this->idle = &Game::defIdleBut;
				this->setPosition(pos);
				this->sprite.setTexture(*(this->idle));
				this->sprite.setTextureRect(intRect);
				this->clicked = &Game::defClickedBut;
				this->hover = &Game::defHoverBut;
				this->font = &Game::defFont;

				this->text.setFont(*(this->font));
				this->text.setString(text);
				this->text.setFillColor(Color::White);
				this->text.setCharacterSize(16);
				this->text.setPosition(
					pos.x + (intRect.width / 2) - (this->text.getGlobalBounds().width / 2),
					pos.y + (intRect.height / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4));

				this->Action= nullptr;
		}
		Button(Vector2f position, Vector2f size, std::string text)
		{
			this->size = size;
			this->idle = &Game::defIdleBut;
			this->setPosition(position);
			this->sprite.setTexture(*(this->idle));
			this->clicked = &Game::defClickedBut;
			this->hover = &Game::defHoverBut;
			this->font = &Game::defFont;

			this->text.setFont(*(this->font));
			this->text.setString(text);
			this->text.setFillColor(Color::White);
			this->text.setCharacterSize(16);

			this->text.setPosition(
				this->sprite.getGlobalBounds().left + (this->size.x / 2) - (this->text.getGlobalBounds().width / 2),
				this->sprite.getGlobalBounds().top + (this->size.y / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4));

			sprite.scale(size.x / idle->getSize().x, size.y / idle->getSize().y);

			this->Action = nullptr;
		}
		Button(std::string texturePath, Vector2f position, Vector2f size, std::string text)
		{
			this->size = size;
			this->image.loadFromFile(texturePath);
			this->uniqueTexture.loadFromImage(image, IntRect(sf::Vector2i(0, 0), (sf::Vector2i)image.getSize()));
			this->idle = &uniqueTexture;
			this->setPosition(position);
			this->sprite.setTexture(*(this->idle));
			this->clicked = &uniqueTexture;
			this->hover = &uniqueTexture;
			this->font = &Game::defFont;

			this->text.setFont(*(this->font));
			this->text.setString(text);
			this->text.setFillColor(Color::White);
			this->text.setCharacterSize(16);

			this->text.setPosition(
				this->sprite.getGlobalBounds().left + (this->size.x / 2) - (this->text.getGlobalBounds().width / 2),
				this->sprite.getGlobalBounds().top + (this->size.y / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4));

			sprite.scale(size.x / idle->getSize().x, size.y / idle->getSize().y);

			this->Action = nullptr;
		}

		~Button() {};

		void setSize(IntRect intRect)
		{
			this->sprite.setTextureRect(intRect);
	    }

		////void setTexture(Texture* idle, Texture* clicked)
		////{
		////	this->idle = idle;
		////	this->clicked = clicked;
		////	//sprite.scale(size.x / idle->getSize().x, size.y / idle->getSize().y);
	 ////   }

		//void setTexture(std::string texturePath)
		//{
		//	this->image.loadFromFile(texturePath);
		//	this->uniqueTexture.loadFromImage(image, IntRect(sf::Vector2i(0, 0), (sf::Vector2i)image.getSize()));
		//	this->sprite.setTexture(this->uniqueTexture);
		//	sprite.scale(this->size.x / image.getSize().x, this->size.y / image.getSize().y);
		//}

		void setFont(Font* font)
		{
			this->font = font;
		}

		void setText(std::string text)
		{
			this->text.setString(text);
		}

		void setDelegate(T func) 
		{
			this->Action = func;
		}

		void setTextRender(bool value)
		{
			renderText = value;
		}

		void update(Vector2f pos) 
		{
			if (isActive && isVisible)
			{
				if (this->sprite.getGlobalBounds().contains(pos))
				{
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						this->sprite.setTexture(*(this->clicked));
						this->sprite.setColor(Color(0, 0, 255)); // test
					}
					else
					{
						this->sprite.setTexture(*(this->hover));
						this->sprite.setColor(Color(255, 0, 0)); // test		
						contains = true;
					}
				}
				else
				{
					this->sprite.setTexture(*(this->idle));
					this->sprite.setColor(Color(255, 255, 255)); // test
					contains = false;
				}
			}
			else
				contains = false;
	    }

		bool isContains(){ return contains; }

		Vector2f getRealPosition(){	return position; }

		int getWidth() { return size.x; }
		
		int getHeight() { return size.y; }


		bool checkClick(Vector2f pos) 
		{
			if (isActive && isVisible)
			{
				if (this->sprite.getGlobalBounds().contains(pos))
				{
					if (Action != nullptr)
						return true;
				}
			}
			return false;
	    }

		void setActive(bool isAct)
		{
			if (!isAct)
			{
				this->sprite.setTexture(*(this->idle));
				this->sprite.setColor(Color(255, 255, 255)); // test
			}
			this->isActive = isAct;
		}

		void render(RenderTarget& target, Vector2f offset)
		{
			if (isVisible)
			{
				this->sprite.setPosition(offset + relPosition);				
				this->text.setPosition(
					this->sprite.getGlobalBounds().left + (this->size.x / 2) - (this->text.getGlobalBounds().width / 2),
					this->sprite.getGlobalBounds().top + (this->size.y / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4));
				if (position ==  Vector2f(0,0))
					position = sprite.getPosition();
				target.draw(this->sprite);
				if (renderText)
					target.draw(this->text);
			}
	    }
};
