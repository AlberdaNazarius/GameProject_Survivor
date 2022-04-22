#pragma once
#include <SFML/Graphics.hpp>
template<typename T>
class Button
{
private:
	sf::Sprite sprite;
	sf::Texture* idle;
	sf::Texture* clicked;
	sf::Texture* hover;
	sf::Font* font;
	sf::Text text;
public:
        T Action;
		Button(sf::Vector2f pos, sf::IntRect intRect, std::string text)
		{
				this->idle = &Game::defIdleBut;
				this->sprite.setPosition(pos);
				this->sprite.setTexture(*(this->idle));
				this->sprite.setTextureRect(intRect);
				this->clicked = &Game::defClickedBut;
				this->hover = &Game::defHoverBut;
				this->font = &Game::defFont;
				this->text.setFont(*(this->font));
				this->text.setString(text);
				this->text.setFillColor(sf::Color::White);
				this->text.setCharacterSize(16);
				this->text.setPosition(
					pos.x + (intRect.width / 2) - (this->text.getGlobalBounds().width / 2),
					pos.y + (intRect.height / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4));
				this->Action= nullptr;
		}
		~Button() {};

		void setPosition(sf::Vector2f pos)
		{
			this->sprite.setPosition(pos);
		}

		void setSize(sf::IntRect intRect)
		{
			this->sprite.setTextureRect(intRect);
	    }

		void setTexture(sf::Texture* idle, sf::Texture* clicked)
		{
			this->idle = idle;
			this->clicked = clicked;
	    }

		void setFont(sf::Font* font)
		{
			this->font = font;
		}

		void setDelegate(T func) 
		{
			this->Action = func;
		}

		void update(sf::Vector2f pos) 
		{
			if (this->sprite.getGlobalBounds().contains(pos))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->sprite.setTexture(*(this->clicked));
					this->sprite.setColor(sf::Color(0, 0, 255)); // test
				}
				else
				{
					this->sprite.setTexture(*(this->hover));
					this->sprite.setColor(sf::Color(255, 0, 0)); // test
				}
			}
			else
			{
				this->sprite.setTexture(*(this->idle));
				this->sprite.setColor(sf::Color(255, 255, 255)); // test
			}
	    }
		bool checkClick(sf::Vector2f pos) 
		{
			if (this->sprite.getGlobalBounds().contains(pos))
			{
				if (Action != nullptr)
					return true;
			}
			return false;
	    }

		void render(sf::RenderTarget& target) 
		{
			target.draw(this->sprite);
			target.draw(this->text);
	    }
};
