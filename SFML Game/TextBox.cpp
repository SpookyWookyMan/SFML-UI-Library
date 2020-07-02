#include "UI.h"

using namespace GUI;

TextBox::TextBox(const sf::Font& font, const char* str) : font(font)
{
	this->SetText(str);
}

TextBox::TextBox(const sf::Font& font) : font(font)
{
	this->SetText("Text");
}

TextBox::TextBox(void)
{
	this->SetText("Text");
}

TextBox::~TextBox(void)
{
}

//Setters


void TextBox::SetPosition(const sf::Vector2f& pos)
{
	this->position = pos;
	this->text.setPosition(this->position);
	this->UpdateGlobalBounds();
}

void TextBox::SetOrigin(const Pivot& pivot)
{
	this->text.setOrigin(SwitchPivot(pivot, this->GetSize()));
}

void TextBox::SetOrigin(const Pivot& pivot, sf::Vector2f* offset)
{
	this->text.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->GetSize()->x + offset->x,
		this->GetSize()->y + offset->y)));
}

void TextBox::SetText(const char* str)
{
	this->text.setString(str);
}

void TextBox::SetColor(const sf::Color& color)
{
	this->text.setFillColor(color);
}

//Getters

sf::Vector2f* TextBox::GetSize(void)
{
	return new sf::Vector2f(this->text.getLocalBounds().width,
		this->text.getLocalBounds().height);
}

const sf::Vector2f& TextBox::GetOrigin(void) const
{
	return this->text.getOrigin();
}

void TextBox::UpdateGlobalBounds(void)
{
	this->globalBounds = this->text.getLocalBounds();
}

void TextBox::Draw(void)
{
	this->manager->window->draw(text);
}