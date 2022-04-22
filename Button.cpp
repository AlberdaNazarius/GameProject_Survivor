//#include <SFML/Graphics.hpp>
//#include "Game.h"
//#include "Button.h"
//template<typename T>
//Button<T>::Button(sf::Vector2f pos, sf::IntRect intRect, std::string text)
//{
//	this->idle = &Game::defIdleBut;
//	this->sprite.setPosition(pos);
//	this->sprite.setTexture(*(this->idle));
//	this->sprite.setTextureRect(intRect);
//	this->clicked = &Game::defClickedBut;
//	this->hover = &Game::defHoverBut;
//	this->font = &Game::defFont;
//	this->text.setFont(*(this->font));
//	this->text.setString(text);
//	this->text.setFillColor(sf::Color::White);
//	this->text.setCharacterSize(16);
//	this->text.setPosition(
//		pos.x + (intRect.width / 2) - (this->text.getGlobalBounds().width / 2),
//		pos.y + (intRect.height / 2) - (this->text.getGlobalBounds().height / 2) - (this->text.getCharacterSize() / 4)
//	);
//	this->pFunc = nullptr;
//}
//template<typename T>
//Button<T>::~Button()
//{
//
//}
//template<typename T>
//void Button<T>::setPosition(sf::Vector2f pos)
//{
//	this->sprite.setPosition(pos);
//}
//template<typename T>
//void Button<T>::setSize(sf::IntRect intRect)
//{
//	this->sprite.setTextureRect(intRect);
//}
//template<typename T>
//void Button<T>::setTexture(sf::Texture* idle, sf::Texture* clicked)
//{
//	this->idle = idle;
//	this->clicked = clicked;
//}
//template<typename T>
//void Button<T>::setFont(sf::Font* font)
//{
//	this->font = font;
//}
//template<typename T>
//void Button<T>::setDelegate(T func)
//{
//	this->pFunc = func;
//}
//template<typename T>
//void Button<T>::update(sf::Vector2f pos)
//{
//	if (this->sprite.getGlobalBounds().contains(pos))
//	{
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		{
//			this->sprite.setTexture(*(this->clicked));
//			this->sprite.setColor(sf::Color(0, 0, 255)); // test
//		}
//		else
//		{
//			this->sprite.setTexture(*(this->hover));
//			this->sprite.setColor(sf::Color(255, 0, 0)); // test
//		}
//	}
//	else
//	{
//		this->sprite.setTexture(*(this->idle));
//		this->sprite.setColor(sf::Color(255, 255, 255)); // test
//	}
//}
//template<typename T>
//bool Button<T>::checkClick(sf::Vector2f pos)
//{
//	if (this->sprite.getGlobalBounds().contains(pos))
//	{
//		if (pFunc != nullptr)
//			this->pFunc();
//		return true;
//	}
//	return false;
//}
//template<typename T>
//void Button<T>::render(sf::RenderTarget& target)
//{
//	target.draw(this->sprite);
//	target.draw(this->text);
//}