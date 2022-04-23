#include <SFML/Graphics.hpp>
#include "UI.h"

UI::UI(Vector2f pos, bool isVis)
{
	this->relPosition = pos;
	this->isVisible = isVis;
}

UI::UI(Vector2f pos)
{
	this->relPosition = pos;
}

UI::UI()
{
	this->relPosition = Vector2f(0, 0);
}

UI::~UI()
{
}

void UI::setPosition(Vector2f pos)
{
	this->relPosition = pos;
}

Vector2f UI::getPosition()
{
	return this->relPosition;
}

void UI::setVisible(bool isVis)
{
	this->isVisible = isVis;
}

bool UI::getVisible()
{
	return this->isVisible;
}

void UI::setActive(bool isAct)
{
	this->isActive = isAct;
}