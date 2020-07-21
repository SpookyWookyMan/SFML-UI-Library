#include "UI.h"

using namespace gui;

Slider::Slider(const float& maxValue, const float& minValue)
	: maxValue{maxValue}, minValue{minValue}, currentValue{maxValue} {
	this->SetBackgroundColor(sf::Color::White);
	this->SetFillColor(sf::Color::Cyan);
	this->SetHandleColor(sf::Color::White);

	this->background.setSize({ 700.0f, 10.0f });
	this->fill.setSize({ 200.0f, 10.0f });
	this->handle.setSize({ 20.0f, 50.0f });

	this->SetOrigin(Widget::Pivot::MID_CENTER);

	this->SetPosition({ 200.0f, 500.0f });

	this->handle.setOutlineColor(sf::Color(100.0f, 100.0f, 100.0f, 255.0f));
	this->handle.setOutlineThickness(1.0f);

}
Slider::Slider(void) : maxValue{100.0f}, minValue{0.0f},
currentValue{100.0f}
{
	this->SetBackgroundColor(sf::Color::White);
	this->SetFillColor(sf::Color::Cyan);
	this->SetHandleColor(sf::Color::White);

	this->background.setSize({700.0f, 10.0f});
	this->fill.setSize({ 200.0f, 10.0f });
	this->handle.setSize({20.0f, 50.0f});

	this->SetOrigin(Widget::Pivot::MID_CENTER);

	this->SetPosition({200.0f, 500.0f});

	this->handle.setOutlineColor(sf::Color(100.0f, 100.0f, 100.0f, 255.0f));
	this->handle.setOutlineThickness(1.0f);
}
Slider::~Slider(void) {
}
void Slider::SetPosition(const sf::Vector2f& pos) {
	this->position = pos;

	this->background.setPosition(this->position);
	this->fill.setPosition(this->position);
	this->handle.setPosition({ this->fill.getPosition().x + this->fill.getSize().x,
			this->position.y + this->GetSize()->y / 2 });

	this->UpdateGlobalBounds();
}
void Slider::SetOrigin(const Pivot& pivot) {
	this->handle.setOrigin(this->SwitchPivot(pivot, new sf::Vector2f(this->handle.getSize().x, this->handle.getSize().y)));
}
void Slider::SetOrigin(const Pivot& pivot, sf::Vector2f* offset) {
}
void Slider::SetSize(const sf::Vector2f& size) {
	this->background.setSize(size);
	this->fill.setSize(size);
}
void Slider::SetHandleSize(const sf::Vector2f& size) {
	this->handle.setSize(size);

	this->UpdateGlobalBounds();
}
void Slider::SetBackgroundColor(const sf::Color& color) {
	this->background.setFillColor(color);
}
void Slider::SetFillColor(const sf::Color& color) {
	this->fill.setFillColor(color);
}
void Slider::SetHandleColor(const sf::Color& color) {
	this->handle.setFillColor(color);
}
sf::Vector2f* Slider::GetSize(void) {
	sf::Vector2f* vec = new sf::Vector2f(this->background.getSize().x, this->background.getSize().y);

	return vec;

	delete vec;
}
const sf::Vector2f& Slider::GetOrigin(void) const {
	return handle.getOrigin();
}
const float& Slider::GetCurrentValue(void) {
	return this->currentValue;
}
void Slider::MouseClick(void) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonPressed) {
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left) {
				mouseHeld = true;
				ClickFunc();
			}
		}
	}
	else {
		if (this->manager->event->type == sf::Event::MouseButtonReleased) {
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left) {
				mouseHeld = false;
			}
		}
	}
}
void Slider::MouseClick(const sf::Mouse::Button& mb) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonPressed) {
			if (this->manager->event->mouseButton.button == mb) {
				mouseHeld = true;
				ClickFunc();
			}
		}
	}
	else {
		if (this->manager->event->type == sf::Event::MouseButtonReleased) {
			if (this->manager->event->mouseButton.button == mb) {
				mouseHeld = false;
			}
		}
	}
}
void Slider::Update(void) {
	if(this->mouseHeld) {
		this->UpdateSlider();
	}

	this->UpdateFunc();
}
void Slider::UpdateGlobalBounds(void) {
	this->globalBounds = handle.getGlobalBounds();
}
void Slider::Draw(void) {
	this->manager->window->draw(this->background);
	this->manager->window->draw(this->fill);
	this->manager->window->draw(this->handle);
}
const float& Slider::NewValue(void) const {
	return (this->fill.getSize().x * this->maxValue) / this->background.getSize().x;
}
void Slider::UpdateSlider(void) {
	float* xmpos = new float((float)sf::Mouse::getPosition(*this->manager->window).x);
	float* xdistance = new float(*xmpos - this->fill.getPosition().x);

	if (*xdistance > this->background.getSize().x) {
		*xdistance = this->background.getSize().x;
	}
	else if (*xdistance < 0.0f) { 
		*xdistance = 0.0f; 
	}
	
	if (*xmpos > this->background.getPosition().x + this->GetSize()->x) {													  
		*xmpos = this->background.getPosition().x + this->GetSize()->x;
	}
	else if (*xmpos < this->background.getPosition().x) {
		*xmpos = this->background.getPosition().x;
	}

	this->handle.setPosition({ *xmpos, this->position.y + this->GetSize()->y / 2 });
	this->UpdateGlobalBounds();
	this->fill.setSize({ *xdistance, this->fill.getSize().y });
	this->currentValue = this->NewValue();

	delete xmpos, xdistance;
}