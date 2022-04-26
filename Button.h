#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"

using namespace sf;

template<typename T>
class Button : public UI
{
private:
	Sprite sprite;
	Texture* idle;
	Texture* clicked;
	Texture* hover;
	Font* font;
	Text text;
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
		~Button() {};

		void setSize(IntRect intRect)
		{
			this->sprite.setTextureRect(intRect);
	    }

		void setTexture(Texture* idle, Texture* clicked)
		{
			this->idle = idle;
			this->clicked = clicked;
	    }

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
					}
				}
				else
				{
					this->sprite.setTexture(*(this->idle));
					this->sprite.setColor(Color(255, 255, 255)); // test
				}
			}
	    }
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

		void render(RenderTarget& target, Vector2f offset)
		{
			if (isVisible)
			{
				this->sprite.setPosition(offset + relPosition);
				this->text.setPosition(
					this->sprite.getGlobalBounds().left + (this->sprite.getTextureRect().width / 2) - (this->text.getGlobalBounds().width / 2),
					this->sprite.getGlobalBounds().top + (this->sprite.getTextureRect().height / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4));
				target.draw(this->sprite);
				target.draw(this->text);
			}
	    }
};
