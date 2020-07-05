#include "UI.h"

using namespace GUI;



InputTextField::InputTextField(const char* str)
{
	this->label.setString(str);
	this->box.setFillColor(sf::Color::White);
}

InputTextField::InputTextField(void)
{
	this->label.setString("Text");
	this->box.setFillColor(sf::Color::White);
}

InputTextField::~InputTextField(void)
{

}

void InputTextField::SetPosition(const sf::Vector2f& pos)
{
	this->position = pos;
	this->text.setPosition(this->position);
	this->UpdateGlobalBounds();
}

void InputTextField::SetOrigin(const Pivot& pivot)
{
	this->text.setOrigin(SwitchPivot(pivot, this->GetSize()));
}

void InputTextField::SetOrigin(const Pivot& pivot, sf::Vector2f* offset)
{
	this->text.setOrigin(SwitchPivotOffset(pivot, this->GetSize(), *offset));
}

sf::Vector2f* InputTextField::GetSize(void)
{
	return new sf::Vector2f(this->text.getLocalBounds().width,
		this->text.getLocalBounds().height);
}

const sf::Vector2f& InputTextField::GetOrigin(void) const
{
	return this->text.getOrigin();
}

void InputTextField::MouseClick(void)
{
	this->typing = true;
	this->ClickFunc();
}

void InputTextField::MouseClick(const sf::Mouse::Button& mb)
{
	this->typing = true;
	this->ClickFunc();
}

void InputTextField::UpdateGlobalBounds(void)
{
	this->globalBounds = this->box.getGlobalBounds();
}

void InputTextField::Update(void)
{
	if (this->textString.length() > 0) 
	{
		this->hasText = true;
	}
	else 
	{
		this->hasText = false;
	}

	if(this->typing)
	{
		if (this->manager->event->type == sf::Event::TextEntered) 
		{
			char keyCode = this->manager->event->text.unicode;

			if (keyCode != 8) 
			{
				this->textString.push_back(keyCode);
			}
			else
			{
				if (this->textString.length() > 0)
				{
					this->textString.pop_back();
				}
			}

			std::cout << this->textString << "\n";

			this->text.setString(this->textString);
		}

		if (!this->IsMouseOver()
			&& this->manager->event->type == sf::Event::MouseButtonReleased)
		{
			if (this->manager->event->mouseButton.button == sf::Mouse::Left
				|| this->manager->event->mouseButton.button == sf::Mouse::Right) 
			{
				this->typing = !this->typing;
			}
		}
	}

	this->UpdateFunc();
}

void InputTextField::Draw(void)
{
	this->manager->window->draw(this->box);
	if(!this->typing && !this->hasText) 
		this->manager->window->draw(this->label);
	else if(this->typing || this->hasText)
		this->manager->window->draw(this->text);
}