#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"


using namespace sf;

class UI
{
protected:
	Vector2f relPosition;	// relative position
	bool isVisible = true;
	bool isActive = true;
public:
	UI(Vector2f pos, bool isVis);
	UI(Vector2f pos);
	UI();
	virtual ~UI();
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	virtual void setVisible(bool isVis);
	bool getVisible();
	virtual void setActive(bool isAct);
	bool getActive();
	virtual void render(RenderTarget& target, Vector2f offset) = 0;
};

class SpriteWithText
{
public:
	SpriteWithText(std::string imageLocation, std::string text, Color color, Vector2f size);

	void SetPosition(float x, float y);
	void SetPosition(Vector2f position);
	void SetTextSize(int characterSize);
	void SetTexPosition(Vector2f position);
	void SetText(std::string text);
	void SetDistanceBetweenObjects(Vector2f distance, SpriteWithText* object, int amount);

	Vector2f GetPosition();
	Vector2f GetTextPosition();
	void Render(RenderWindow& window);

private:
	Image image;
	Texture texture;
	Sprite sprite;
	Text text;
	Vector2f size;
	Vector2f position;
};