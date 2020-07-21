#include "UI.h"

using namespace gui;

InputTextField::InputTextField(const char* str, const char* path) : typing{false}, hasText{false} {
	if (!this->font.loadFromFile(path))
		std::cout << "FAILURE: Couldn't load font from file\n";

	this->SetFont(font);
	this->label.setFillColor(sf::Color(140, 140, 140, 255));
	this->text.setFillColor(sf::Color(0, 0, 0, 255));
	this->label.setString(str);
	this->box.setFillColor(sf::Color::White);
	this->box.setSize({200.0f, 50.0f});
	this->SetPosition({0.0f, 0.0f});
	this->UpdateGlobalBounds();
}
InputTextField::InputTextField(const char* str, const sf::Font& font) : typing(false), hasText(false) {
	this->SetFont(font);
	this->text.setFillColor(sf::Color(140, 140, 140, 255));
	this->label.setFillColor(sf::Color(0, 0, 0, 255));
	this->label.setString(str);
	this->box.setFillColor(sf::Color::White);
	this->box.setSize({ 200.0f, 50.0f });
	this->SetPosition({ 0.0f, 0.0f });
	this->UpdateGlobalBounds();
}
InputTextField::~InputTextField(void) {
}
void InputTextField::SetPosition(const sf::Vector2f& pos) {
	this->position = pos;
	this->box.setPosition(this->position);
	this->label.setPosition(this->position);
	this->text.setPosition(this->position);
	this->UpdateGlobalBounds();
}
void InputTextField::SetOrigin(const Pivot& pivot) {
	this->text.setOrigin(SwitchPivot(pivot, this->GetTextSize(this->text)));
	this->label.setOrigin(SwitchPivot(pivot, this->GetTextSize(this->label)));
	this->box.setOrigin(SwitchPivot(pivot, this->GetSize()));
}
void InputTextField::SetOrigin(const Pivot& pivot, sf::Vector2f* offset) {
	this->text.setOrigin(SwitchPivotOffset(pivot, this->GetTextSize(this->text), *offset));
	this->label.setOrigin(SwitchPivotOffset(pivot, this->GetTextSize(this->label), *offset));
	this->box.setOrigin(SwitchPivotOffset(pivot, this->GetSize(), *offset));
}
void InputTextField::SetFont(const sf::Font& font) {
	this->text.setFont(font);
	this->label.setFont(font);
}
void InputTextField::SetFont(const char* path) {
	if(!font.loadFromFile(path))
		std::cout << "FAILURE: Couldn't load font from file\n";

	this->text.setFont(this->font);
	this->label.setFont(this->font);
}
sf::Vector2f* InputTextField::GetSize(void) {
	return new sf::Vector2f(this->text.getLocalBounds().width,
		this->text.getLocalBounds().height);
}
const sf::Vector2f& InputTextField::GetOrigin(void) const {
	return this->text.getOrigin();
}
const std::string& InputTextField::GetString(void) const {
	return this->textString;
}
void InputTextField::MouseClick(void) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonPressed) {
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left) {
				this->mouseHeld = true;
				this->typing = true;
				this->ClickFunc();
			}
		}
	}
}
void InputTextField::MouseClick(const sf::Mouse::Button& mb) {
	if (IsMouseOver()) {
		if (this->manager->event->type == sf::Event::MouseButtonPressed) {
			if (this->manager->event->mouseButton.button == mb) {
				this->mouseHeld = true;
				this->typing = true;
				this->ClickFunc();
			}
		}
	}
}
void InputTextField::UpdateGlobalBounds(void) {
	this->globalBounds = this->box.getGlobalBounds();
}
void InputTextField::Events(void) {
	if (this->textString.length() > 0) {
		this->hasText = true;
	}
	else {
		this->hasText = false;
	}

	if (this->typing) {
		if (this->manager->event->type == sf::Event::TextEntered) {
			char keyCode = this->manager->event->text.unicode;
			
			if (keyCode == 27) typing = !typing;
			else if (keyCode != 8) {
				this->textString.push_back(keyCode);
			}
			else {
				if (this->textString.length() > 0) {
					this->textString.pop_back();
				}
			}

			this->text.setString(this->textString);
		}

		if (!this->IsMouseOver()
			&& this->manager->event->type == sf::Event::MouseButtonReleased) {
			if (this->manager->event->mouseButton.button == sf::Mouse::Left
				|| this->manager->event->mouseButton.button == sf::Mouse::Right) {
				this->typing = !this->typing;
			}
		}
	}

	this->MouseEnter();
	this->MouseExit();
	this->MouseClick();
	this->MouseRelease();
}
void InputTextField::Update(void) {
	this->UpdateFunc();
}
void InputTextField::Draw(void) {
	this->manager->window->draw(this->box);
	if(!this->typing && !this->hasText) 
		this->manager->window->draw(this->label);
	else if(this->typing || this->hasText)
		this->manager->window->draw(this->text);
}
sf::Vector2f* InputTextField::GetTextSize(const sf::Text& text) const {
	sf::Vector2f* vec = new sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);

	return vec;

	delete vec;
}