#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"
#include "Button.h"

using namespace sf;

class Container : public UI
{
protected:
	std::vector<UI*> childs;
public:
	virtual ~Container();
	void render(RenderTarget& target, Vector2f offset);
	void setVisible(bool isVis);
	void setActive(bool isAct);
	void addChild(UI* child);
	void removeChild(UI* child);
};