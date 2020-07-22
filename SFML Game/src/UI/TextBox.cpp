#include "UI.h"

using namespace gui;

TextBox::TextBox(const char* path, const char* str) {
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(path))
		std::cout << "Failed to load font from: " << path << "\n";

	this->font = *font;
	this->SetFont(*font);
	this->SetText(str);
	this->SetColor(sf::Color::White);
	this->text.setCharacterSize(72);

	delete font;
}
TextBox::TextBox(const char* path) {
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(path))
		std::cout << "Failed to load font from: " << path << "\n";

	this->font = *font;
	this->SetFont(*font);
	this->SetText("Text");
	this->SetColor(sf::Color::White);
	this->text.setCharacterSize(72);

	delete font;
}
TextBox::TextBox(const sf::Font& font, const char* str) {
	this->SetFont(font);
	this->SetText(str);
}
TextBox::TextBox(const sf::Font& font) {
	this->SetFont(font);
	this->SetText("Text");
}
TextBox::TextBox(void) {
}
TextBox::~TextBox(void) {
}
void TextBox::SetPosition(const sf::Vector2f& pos) {
	this->position = pos;
	this->text.setPosition(this->position);
	this->UpdateGlobalBounds();
}
void TextBox::SetOrigin(const Pivot& pivot) {
	this->text.setOrigin(SwitchPivot(pivot, this->GetSize()));
}
void TextBox::SetOrigin(const Pivot& pivot, sf::Vector2f* offset) {
	this->text.setOrigin(SwitchPivotOffset(pivot, this->GetSize(), *offset));
}
void TextBox::SetText(const char* str) {
	this->text.setString(str);
}
void TextBox::SetFont(const sf::Font& font) {
	this->font = font;
	this->text.setFont(this->font);
}
void TextBox::SetFont(const char* path) {
	sf::Font* font = new sf::Font();
	
	if (!font->loadFromFile(path))
		std::cout << "Failed to load font from: " << path << "\n";

	this->font = *font;
	this->text.setFont(this->font);

	delete font;
}
void TextBox::SetColor(const sf::Color& color) {
	this->text.setFillColor(color);
}
void TextBox::SetSize(const unsigned int&& size) {
	this->text.setCharacterSize(size);
	this->UpdateGlobalBounds();

	std::cout << "WARNING: Always call SetSize before SetOrigin to avoid "
		<< "setting the wrong origin.\n";
}
sf::Vector2f* TextBox::GetSize(void) {
	return new sf::Vector2f(this->text.getLocalBounds().width,
		this->text.getLocalBounds().height);
}
const sf::Vector2f& TextBox::GetOrigin(void) const {
	return this->text.getOrigin();
}
void TextBox::UpdateGlobalBounds(void) {
	this->globalBounds = this->text.getGlobalBounds();
}
void TextBox::Draw(void) {
		this->manager->window->draw(this->text);
}