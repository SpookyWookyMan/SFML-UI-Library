#include "UI.h"

using namespace gui;

void Widget::SetManager(UIManager* m) {
	this->manager = m;
	this->manager->InsertWidget(this);
}
void Widget::SetActive(const bool& active) {
	this->active = active;
}
const bool& Widget::IsActive(void) const {
	return active;
}
const bool& Widget::IsHidden(void) const {
	return hidden;
}
inline bool Widget::IsMouseOver(void) {
	if (active) {
		std::unique_ptr<sf::Vector2f> pos(new sf::Vector2f(sf::Mouse::getPosition(*manager->window)));
		return globalBounds.contains(*pos);
	}
	else {
		return false;
	}
}
void Widget::Hide(const bool& hide) {
	this->hidden = hide;
}
void Widget::MouseEnter(void) {
	if (IsMouseOver()) {
		MouseEnterFunc();
	}
}
void Widget::MouseExit(void) {
	if (!IsMouseOver()) {
		MouseExitFunc();
	}
}
void Widget::MouseRelease(const sf::Mouse::Button& mb) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonReleased) {
			if (this->manager->event->mouseButton.button == mb) {
				mouseHeld = false;
				ReleaseFunc();
			}
		}
	}
}
void Widget::MouseClick(void) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonPressed) {
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left) {
				mouseHeld = true;
				ClickFunc();
			}
		}
	}
}
void Widget::MouseClick(const sf::Mouse::Button& mb) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonPressed) {
			if (this->manager->event->mouseButton.button == mb) {
				mouseHeld = true;
				ClickFunc();
			}
		}
	}
}
void Widget::MouseRelease(void) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonReleased) {
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left) {
				mouseHeld = false;
				ReleaseFunc();
			}
		}
	}
}
void Widget::Events(void) 
{
	this->MouseEnter();
	this->MouseExit();
	this->MouseClick();
	this->MouseRelease();
}
void Widget::Update(void) {
	UpdateFunc();
}
sf::Vector2f Widget::SwitchPivot(const Pivot& pivot, sf::Vector2f* v) {
	std::unique_ptr<sf::Vector2f> dim(v);
	sf::Vector2f* vec = nullptr;

	switch (pivot) {
	case Widget::Pivot::TOP_LEFT: vec = new sf::Vector2f(0.0f, 0.0f); break;
	case Widget::Pivot::TOP_CENTER: vec = new sf::Vector2f(dim->x / 2, 0.0f); break;
	case Widget::Pivot::TOP_RIGHT: vec = new sf::Vector2f(dim->x, 0.0f); break;

	case Widget::Pivot::MID_LEFT: vec = new sf::Vector2f(0.0f, dim->y / 2); break;
	case Widget::Pivot::MID_CENTER: vec = new sf::Vector2f(dim->x / 2, dim->y / 2); break;
	case Widget::Pivot::MID_RIGHT: vec = new sf::Vector2f(dim->x, dim->y / 2); break;

	case Widget::Pivot::BOT_LEFT: vec = new sf::Vector2f(0.0f, dim->y); break;
	case Widget::Pivot::BOT_CENTER: vec = new sf::Vector2f(dim->x / 2, dim->y); break;
	case Widget::Pivot::BOT_RIGHT: vec = new sf::Vector2f(dim->x, dim->y); break;

	default: vec = new sf::Vector2f(0.0f, 0.0f); break;
	}

	return *vec;

	delete vec;
}
sf::Vector2f Widget::SwitchPivotOffset(const Pivot& pivot, sf::Vector2f* v, const sf::Vector2f& offset) {
	std::unique_ptr<sf::Vector2f> dim(v);
	sf::Vector2f* vec = nullptr;

	switch (pivot) {
	case Widget::Pivot::TOP_LEFT: vec = new sf::Vector2f(0.0f + offset.x, 0.0f + offset.y); break;
	case Widget::Pivot::TOP_CENTER: vec = new sf::Vector2f((dim->x / 2) + offset.x, 0.0f + offset.y); break;
	case Widget::Pivot::TOP_RIGHT: vec = new sf::Vector2f(dim->x + offset.x, 0.0f + offset.x); break;

	case Widget::Pivot::MID_LEFT: vec = new sf::Vector2f(0.0f + offset.x, (dim->y / 2) + offset.y); break;
	case Widget::Pivot::MID_CENTER: vec = new sf::Vector2f((dim->x / 2) + offset.x, (dim->y / 2) + offset.y); break;
	case Widget::Pivot::MID_RIGHT: vec = new sf::Vector2f(dim->x + offset.x, (dim->y / 2) + offset.y); break;

	case Widget::Pivot::BOT_LEFT: vec = new sf::Vector2f(0.0f + offset.x, dim->y + offset.y); break;
	case Widget::Pivot::BOT_CENTER: vec = new sf::Vector2f((dim->x / 2) + offset.x, dim->y + offset.y); break;
	case Widget::Pivot::BOT_RIGHT: vec = new sf::Vector2f(dim->x + offset.x, dim->y + offset.y); break;

	default: vec = new sf::Vector2f(0.0f + offset.x, 0.0f + offset.y); break;
	}

	return *vec;

	delete vec;
}