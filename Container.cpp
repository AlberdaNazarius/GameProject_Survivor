#include "Container.h"

Container::~Container()
{
	this->childs.clear();
}

void Container::render(RenderTarget& target, Vector2f offset)
{
	if (isVisible)
		for (int i = 0; i < this->childs.size(); i++)
			this->childs[i]->render(target, offset + relPosition);
}

void Container::setVisible(bool isVis)
{
	this->setActive(isVis);
	this->isVisible = isVis;
}

void Container::setActive(bool isAct)
{
	this->isActive = isAct;
	for (int i = 0; i < this->childs.size(); i++)
		this->childs[i]->setActive(isAct);
}

void Container::addChild(UI* child)
{
	this->childs.push_back(child);
}

void Container::removeChild(UI* child)
{
	for (int i = 0; i < this->childs.size(); i++)
		if (&this->childs[i] == &child)
		{
			this->childs.erase(childs.begin() + i);
			break;
		}
}