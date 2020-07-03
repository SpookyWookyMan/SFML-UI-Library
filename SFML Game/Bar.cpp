#include "UI.h"

using namespace GUI;



Bar::Bar(const sf::Vector2f& dim, const float& maxValue, const float& minValue)
{
	this->rectSize = dim;
	this->SetSize(rectSize);

	this->maxValue = maxValue;
	this->minValue = minValue;

	this->valueBar.setFillColor(sf::Color::Green);
	this->backgroundBar.setFillColor(sf::Color::Red);
	this->background.setFillColor(sf::Color::Blue);

}

Bar::Bar(const sf::Vector2f& dim)
{
	this->rectSize = dim;
	this->SetSize(rectSize);

	this->maxValue = maxValue;
	this->minValue = minValue;

	this->valueBar.setFillColor(sf::Color::Green);
	this->backgroundBar.setFillColor(sf::Color::Red);
	this->background.setFillColor(sf::Color::Blue);

}

Bar::Bar(void)
{
	std::unique_ptr<sf::Vector2f>dim(new sf::Vector2f(200.0f, 50.0f));

	this->SetSize(*dim);

	this->maxValue = 100.0f;
	this->minValue = 0.0f;

	this->valueBar.setFillColor(sf::Color::Green);
	this->backgroundBar.setFillColor(sf::Color::Red);
	this->background.setFillColor(sf::Color::Blue);
}

Bar::~Bar(void)
{
}

void Bar::SetPosition(const sf::Vector2f& pos)
{
	this->position = pos;
	this->UpdateBarPos();
}

void Bar::SetOrigin(const Pivot& pivot) 
{
	this->valueBar.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x, this->GetSize()->y)));
	this->backgroundBar.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x, this->GetSize()->y)));
	this->background.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x, this->GetSize()->y)));
}

void Bar::SetOrigin(const Pivot& pivot, sf::Vector2f* offset) 
{
	this->valueBar.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x + offset->x,
		this->GetSize()->y + offset->y)));
	this->backgroundBar.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x + offset->x,
		this->GetSize()->y + offset->y)));
	this->background.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x + offset->x,
		this->GetSize()->y + offset->y)));
}

void Bar::SetSize(const sf::Vector2f& dim)
{
	this->valueBar.setSize(dim);
	this->backgroundBar.setSize(dim);
	this->background.setSize(dim);
}

sf::Vector2f* Bar::GetSize(void) 
{
	return new sf::Vector2f(this->valueBar.getSize().x, this->valueBar.getSize().y);
}

const sf::Vector2f& Bar::GetOrigin(void) const 
{
	return this->valueBar.getOrigin();
}

void Bar::ChangeValueBy(const float&& val)
{
	//this->currentValue += val;
	float* x = new float[(float)(this->currentValue + val) * GetSize()->x];

	std::unique_ptr<sf::Vector2f> size(new sf::Vector2f(*x + currentValue, this->GetSize()->y));

	this->currentValue += val;

	this->rectSize = *size;

	delete size;
	delete x;

}

void Bar::UpdateGlobalBounds(void)
{
	this->globalBounds = this->valueBar.getGlobalBounds();
}

void Bar::Draw(void) 
{
	if (!hidden) 
	{
		this->manager->window->draw(this->background);
		this->manager->window->draw(this->backgroundBar);
		this->manager->window->draw(this->valueBar);
	}
}

void Bar::UpdateBarPos(void)
{
	this->valueBar.setPosition(this->position);
	this->backgroundBar.setPosition(this->position);
	this->background.setPosition(this->position);
}