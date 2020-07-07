#include "UI.h"

using namespace GUI;

DropDownList::DropDownList(void) 
{

}

DropDownList::~DropDownList(void) 
{
}

void DropDownList::SetPosition(const sf::Vector2f& pos)
{
	this->position = position;
	this->optionDisplay.setPosition(this->position);
}

void DropDownList::SetOrigin(const Pivot& pivot)
{
	this->optionDisplay.setOrigin(this->SwitchPivot(pivot, this->GetSize()));
}

void DropDownList::SetOrigin(const Pivot& pivot, sf::Vector2f* offset)
{
	this->optionDisplay.setOrigin(this->SwitchPivotOffset(pivot, this->GetSize(), *offset));
}

sf::Vector2f* DropDownList::GetSize(void)
{
	sf::Vector2f* vec = new sf::Vector2f(this->optionDisplay.getSize().x, this->optionDisplay.getSize().y);

	return vec;

	delete vec;
}

const sf::Vector2f& DropDownList::GetOrigin(void) const
{
	return this->optionDisplay.getOrigin();
}

void DropDownList::AddOption(const char* optionString)
{
	Option* option = new Option(optionString);

	this->list.push_back(option);
}

void DropDownList::UpdateGlobalBounds(void)
{
	this->globalBounds = this->optionDisplay.getGlobalBounds();
}

void DropDownList::Draw(void)
{
	this->manager->window->draw(this->optionDisplay);
	if(showOptions)
		for (Option*& o : list) 
		{
			this->manager->window->draw(o->optionRect);
			this->manager->window->draw(o->text);
		}
}

void DropDownList::UpdateOptionBoxPosition(void)
{
	sf::Vector2f* pos = new sf::Vector2f(this->optionDisplay.getPosition());

	for (auto i = 0; i < sizeof(this->list) / sizeof(Option); i++)
	{
		this->list.at(i)->optionRect.setPosition({pos->x, pos->y + this->GetSize()->y * i });
	}
}