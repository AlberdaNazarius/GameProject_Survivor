#pragma once
#include <SFML/Graphics.hpp>
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
	virtual void render(RenderTarget& target, Vector2f offset) = 0;
};