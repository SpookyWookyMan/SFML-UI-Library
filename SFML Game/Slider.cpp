#include "UI.h"

using namespace GUI;

Slider::Slider(const float& maxValue, const float& minValue)
	: maxValue(maxValue), minValue(minValue), currentValue(maxValue)
{
	this->SetBackgroundColor(sf::Color::White);
	this->SetFillColor(sf::Color::Cyan);
	this->SetHandleColor(sf::Color::White);

	this->handle.setOutlineColor(sf::Color(100.0f, 100.0f, 100.0f, 255.0f));
	this->handle.setOutlineThickness(1.0f);

}

Slider::Slider(void) : maxValue(100.0f), minValue(0.0f),
currentValue(100.0f)
{
	this->SetBackgroundColor(sf::Color::White);
	this->SetFillColor(sf::Color::Cyan);
	this->SetHandleColor(sf::Color::White);

	this->handle.setOutlineColor(sf::Color(100.0f, 100.0f, 100.0f, 255.0f));
	this->handle.setOutlineThickness(1.0f);
}

Slider::~Slider(void)
{
}

void Slider::SetPosition(const sf::Vector2f& pos)
{
	this->position = pos;

	this->background.setPosition(this->position);
	this->fill.setPosition(this->position);
	//handle position w/ offset
}

void Slider::SetOrigin(const Pivot& pivot)
{
	//this->background.setOrigin(SwitchPivot(pivot, this->GetSize()));
	//this->fill.setOrigin(SwitchPivot(pivot, this->GetSize()));
}

void Slider::SetOrigin(const Pivot& pivot, sf::Vector2f* offset)
{
	//this->valueBar.setOrigin(SwitchPivotOffset(pivot, this->GetSize(), *offset));
}

void Slider::SetSize(const sf::Vector2f& size)
{
	this->background.setSize(size);
	this->fill.setSize(size);
}

void GUI::Slider::SetHandleSize(const sf::Vector2f& size)
{
	this->handle.setSize(size);
}

void Slider::SetBackgroundColor(const sf::Color& color)
{
	this->background.setFillColor(color);
}

void Slider::SetFillColor(const sf::Color& color)
{
	this->fill.setFillColor(color);
}

sf::Vector2f* Slider::GetSize(void)
{
	sf::Vector2f* vec = new sf::Vector2f(this->background.getSize().x, this->background.getSize().y);

	return vec;

	delete vec;
}

const sf::Vector2f& Slider::GetOrigin(void) const
{
	return handle.getOrigin();
}

const float& Slider::GetCurrentValue(void)
{
	return this->currentValue;
}

void Slider::MouseClick(void)
{
	if (IsMouseOver())
	{
		if (this->manager->event->type == sf::Event::MouseButtonPressed)
		{
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left)
			{
				mouseHeld = true;
				ClickFunc();
			}
		}
	}
}

void Slider::MouseClick(const sf::Mouse::Button& mb)
{
	if (IsMouseOver())
	{
		if (this->manager->event->type == sf::Event::MouseButtonPressed)
		{
			if (this->manager->event->mouseButton.button == mb)
			{
				mouseHeld = true;
				ClickFunc();
			}
		}
	}
}

void Slider::Update(void)
{
	if(this->mouseHeld)
	{
		this->handle.setPosition({ this->fill.getPosition().x + this->fill.getSize().x,
			this->position.y + this->GetSize()->y / 2 });
		this->fill.setSize({NewWidth(), this->fill.getSize().y});
		this->currentValue = NewValue();
	}

	this->UpdateFunc();
}

void Slider::UpdateGlobalBounds(void)
{
	this->globalBounds = handle.getGlobalBounds();
}

void Slider::Draw(void)
{
	this->manager->window->draw(this->background);
	this->manager->window->draw(this->fill);
	this->manager->window->draw(this->handle);
}

const float& Slider::NewValue(void) const 
{
	return (this->fill.getSize().x * this->maxValue) / this->background.getSize().x;
}

const float& Slider::NewWidth(void) const 
{
	std::unique_ptr<sf::Vector2f> mousePos = std::make_unique<sf::Vector2f>(sf::Mouse::getPosition(*this->manager->window));
	std::unique_ptr<float> xdistance = std::make_unique<float>(mousePos.get()->x - this->fill.getPosition().x);

	if (*xdistance > this->background.getSize().x) 
	{
		*xdistance = this->background.getSize().x;
	}
	else if (*xdistance < 0.0f) 
	{
		*xdistance = 0.0f;
	}

	return *xdistance;
}