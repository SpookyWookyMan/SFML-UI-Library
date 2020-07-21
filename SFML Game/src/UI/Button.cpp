#include "UI.h"

using namespace gui;

Button::Button(const sf::Texture& normTxtr)
	: normal{normTxtr} {
	this->SetText("Button");
	this->SetTextSize(72);
	this->UpdateTextPosition();

	this->sprite.setTexture(normal);
	this->UpdateGlobalBounds();
}
Button::Button(void) {
	this->SetText("Button");
	this->SetTextSize(72);
	this->UpdateTextPosition();

	std::cout << "WARNING: Default constructor used. Load a texture to display the button.\n";
	std::cout << "Current texture is: " << this->sprite.getTexture() << "\n";
}
Button::~Button(void){
}
void Button::SetPosition(const sf::Vector2f& pos) {
	this->position = pos;
	this->sprite.setPosition(this->position);
	this->UpdateTextPosition();
	this->UpdateGlobalBounds();
}
void Button::SetOrigin(const Pivot& pivot) {
	this->sprite.setOrigin(SwitchPivot(pivot, this->GetSize()));
}
void Button::SetOrigin(const Pivot& pivot, sf::Vector2f* offset) {
	this->sprite.setOrigin(SwitchPivotOffset(pivot, this->GetSize(), *offset));
}
void Button::SetTexture(const sf::Texture& texture) {
	this->sprite.setTexture(texture);
	this->UpdateGlobalBounds();
}
void Button::SetTextFont(const sf::Font& font) {
	this->textFont = font;
	this->text.setFont(this->textFont);
}
void Button::SetTextFont(const char* path) {
	sf::Font* font = new sf::Font();

	if(!font->loadFromFile(path))
		printf("Failed to load texture from: %p", path);

	this->textFont = *font;
	this->text.setFont(this->textFont);

	font = nullptr;
	delete font;
}
void Button::SetTextSize(const unsigned int&& size) {
	this->text.setCharacterSize(size);
}
void Button::SetTextColor(const sf::Color& clr) {
	this->text.setFillColor(clr);
}
void Button::SetTextOrigin(const Pivot& pivot) {
	this->text.setOrigin(SwitchPivot(pivot, new sf::Vector2f(this->text.getLocalBounds().width,
		this->text.getLocalBounds().height)));
}
void Button::SetTextOrigin(const Pivot& pivot, sf::Vector2f* offset) {
	this->text.setOrigin(SwitchPivotOffset(pivot, new sf::Vector2f(this->text.getLocalBounds().width,
		this->text.getLocalBounds().height), *offset));
}
void Button::SetText(const char* str){
	this->text.setString(str);
}
sf::Vector2f* Button::GetSize(void) {
	return new sf::Vector2f(this->sprite.getTexture()->getSize().x * this->sprite.getScale().x,
		this->sprite.getTexture()->getSize().y * this->sprite.getScale().y);
}
const sf::Vector2f& Button::GetOrigin(void) const {
	return this->sprite.getOrigin();
}
void Button::UpdateGlobalBounds(void) {
	this->globalBounds = this->sprite.getGlobalBounds();
}
void Button::LoadTexture(const std::string& path, TextureType ttype) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture);
	if (!texture->loadFromFile(path))
		printf("Failed to load texture from: %p", path);

	switch (ttype) {
	case TextureType::NORMAL: this->normal = *texture; break;
	case TextureType::HIGHLIGHT: this->highlight = *texture; break;
	case TextureType::CLICKED: this->clicked = *texture; break;
	}
}

void Button::LoadTextures(const char* path, const char* _path, const char* __path) {
	std::unique_ptr<sf::Texture> nl(new sf::Texture);
	std::unique_ptr<sf::Texture> hl(new sf::Texture);
	std::unique_ptr<sf::Texture> cd(new sf::Texture);

	nl->loadFromFile(path);
	hl->loadFromFile(_path);
	cd->loadFromFile(__path);

	this->normal = *nl;
	this->highlight = *hl;
	this->clicked = *cd;
}
void Button::HideText(const bool& b) {
	this->hideText = b;
}
void Button::Draw(void) {
	this->manager->window->draw(this->sprite);
	if (!this->hideText) {
		this->manager->window->draw(this->text);
	}
}
void Button::UpdateTextPosition(void) {
	this->text.setPosition(this->position);
}