#include "UI.h"

using namespace gui;

CheckBox::CheckBox(const float&& size) 
{
	this->SetSize({size, size});
	this->SetCheckmarkColor(sf::Color::Red);
	this->SetBackgroundColor(sf::Color::White);
	this->SetOutlineColor(sf::Color::Green);
	this->SetOrigin(Widget::Pivot::MID_CENTER);
	this->SetPosition({0.0f, 0.0f});
	this->checked = true;
}

CheckBox::CheckBox(void)
{
	this->SetSize({50.0f, 50.0f});
	this->SetCheckmarkColor(sf::Color::Red);
	this->SetBackgroundColor(sf::Color::White);
	this->SetOutlineColor(sf::Color::Green);
	this->SetOrigin(Widget::Pivot::MID_CENTER);
	this->SetPosition({ 0.0f, 0.0f });
}

CheckBox::~CheckBox(void)
{
}

void CheckBox::SetSize(const sf::Vector2f& size)
{
	std::unique_ptr<sf::Vector2f> checkMarkSize(new sf::Vector2f(0.85f * size.x, 0.85f * size.y));

	this->background.setSize(size);
	this->checkMark.setSize(*checkMarkSize);

	this->UpdateGlobalBounds();

}

void CheckBox::SetPosition(const sf::Vector2f& pos)
{
	this->position = pos;
	this->background.setPosition(pos);
	this->checkMark.setPosition(pos);

	this->UpdateGlobalBounds();
}

void CheckBox::SetOrigin(const Pivot& pivot)
{
	this->checkMark.setOrigin(this->SwitchPivot(pivot, new sf::Vector2f(this->checkMark.getSize().x, this->checkMark.getSize().y)));
	this->background.setOrigin(this->SwitchPivot(pivot, this->GetSize()));
}

void CheckBox::SetOrigin(const Pivot& pivot, sf::Vector2f* offset)
{
	this->checkMark.setOrigin(this->SwitchPivotOffset(pivot, this->GetSize(), *offset));
	this->background.setOrigin(this->SwitchPivotOffset(pivot, this->GetSize(), *offset));
}

void CheckBox::SetCheckmarkColor(const sf::Color& color)
{
	this->checkMark.setFillColor(color);
}

void CheckBox::SetBackgroundColor(const sf::Color& color)
{
	this->background.setFillColor(color);
}

void CheckBox::SetOutlineColor(const sf::Color& color)
{
	this->background.setOutlineColor(color);
}

void CheckBox::SetOutlineThickness(const float& thickness)
{
	this->outlineThickness = thickness;
	this->background.setOutlineThickness(this->outlineThickness);
}

sf::Vector2f* CheckBox::GetSize(void)
{
	sf::Vector2f* vec = new sf::Vector2f(this->background.getSize().x, this->background.getSize().y);

	return vec;

	delete vec;
}

const sf::Vector2f& CheckBox::GetOrigin(void) const
{
	return this->background.getOrigin();
}

const bool& CheckBox::IsChecked(void) const
{
	return this->checked;
}

void CheckBox::UpdateGlobalBounds(void)
{
	this->globalBounds = this->background.getGlobalBounds();
}

void CheckBox::MouseRelease(void)
{
	if (IsMouseOver())
	{
		if (this->manager->event->type == sf::Event::MouseButtonReleased)
		{
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left)
			{
				mouseHeld = false;
				this->checked = !checked;
				ReleaseFunc();
			}
		}
	}
}

void CheckBox::MouseRelease(const sf::Mouse::Button& mb)
{
	if (IsMouseOver())
	{
		if (this->manager->event->type == sf::Event::MouseButtonReleased)
		{
			if (this->manager->event->mouseButton.button == mb)
			{
				mouseHeld = false;
				this->checked = !checked;
				ReleaseFunc();
			}
		}
	}
}

void CheckBox::Update(void) 
{
	if(this->IsMouseOver())
	{
		this->SetOutlineThickness(this->outlineThickness);
	}
	else 
	{
		this->background.setOutlineThickness(0.0f);
	}

	this->UpdateFunc();
}

void CheckBox::Draw(void)
{
	this->manager->window->draw(this->background);
	if(checked) this->manager->window->draw(this->checkMark);
}

