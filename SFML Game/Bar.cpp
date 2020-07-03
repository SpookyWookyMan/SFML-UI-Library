#include "UI.h"

using namespace GUI;



Bar::Bar(const sf::Vector2f& dim, const float& maxValue, const float& minValue)
{
	this->SetSize(dim);

	this->maxValue = maxValue;
	this->minValue = minValue;

	this->currentValue = this->maxValue;

	this->valueBar.setFillColor(sf::Color::Green);
	this->backgroundBar.setFillColor(sf::Color::Red);
	this->background.setFillColor(sf::Color::Blue);
}

Bar::Bar(const sf::Vector2f& dim)
{
	this->SetSize(dim);

	this->maxValue = maxValue;
	this->minValue = minValue;

	this->currentValue = this->maxValue;

	this->valueBar.setFillColor(sf::Color::Green);
	this->backgroundBar.setFillColor(sf::Color::Red);
	this->background.setFillColor(sf::Color::Blue);
}

Bar::Bar(void)
{
	std::unique_ptr<sf::Vector2f>dim(new sf::Vector2f(700.0f, 10.0f));

	this->SetSize(*dim);

	this->maxValue = 100.0f;
	this->minValue = 0.0f;

	this->currentValue = this->maxValue;

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
	return new sf::Vector2f(this->background.getSize().x, this->background.getSize().y);
}

const sf::Vector2f& Bar::GetOrigin(void) const 
{
	return this->valueBar.getOrigin();
}

void Bar::ChangeValueBy(const float&& val)
{
	this->currentValue += val;

	if (this->currentValue > this->maxValue) this->currentValue = this->maxValue;
	else if (this->currentValue < this->minValue) this->currentValue = this->minValue;

	float* x = new float((this->currentValue) * GetSize()->x / this->maxValue);
	std::unique_ptr<sf::Vector2f> size(new sf::Vector2f(*x, this->GetSize()->y));

	this->valueBar.setSize(*size);

	delete x;
}

void Bar::UpdateGlobalBounds(void)
{
	this->globalBounds = this->valueBar.getGlobalBounds();
}

void Bar::Update(void)
{
	if (this->showBackBar) 
	{
		if (this->backgroundBar.getSize().x > this->valueBar.getSize().x)
		{
			timer = clock.getElapsedTime();

			if (timer.asMilliseconds() >= this->bBarDelay && !this->decreaseVal)
			{
				this->decreaseVal = true;
				this->clock.restart();
				printf("got here\n");
			}
			if (decreaseVal && timer.asMilliseconds() >= bBarDecraseInterval)
			{
				std::unique_ptr<sf::Vector2f> size(new sf::Vector2f(this->backgroundBar.getSize().x - bBarDecreaseAmount, this->backgroundBar.getSize().y));
				this->backgroundBar.setSize(*size);

				this->clock.restart();
			}
		}
		else 
		{
			this->decreaseVal = false;
		}
	}

	this->UpdateFunc();
}

void Bar::Draw(void)
{
	if (!hidden) 
	{
		this->manager->window->draw(this->background);
		if(showBackBar) this->manager->window->draw(this->backgroundBar);
		this->manager->window->draw(this->valueBar);
	}
}

void Bar::UpdateBarPos(void)
{
	this->valueBar.setPosition(this->position);
	this->backgroundBar.setPosition(this->position);
	this->background.setPosition(this->position);
}