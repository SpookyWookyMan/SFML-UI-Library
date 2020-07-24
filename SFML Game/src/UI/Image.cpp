#include "UI.h"

using namespace gui;

Image::Image(const char* path) {
	if (!this->texture.loadFromFile(path))
		printf("FAILURE TO LOAD TEXTURE FROM FILE");

	this->sprite.setTexture(this->texture);
}
Image::Image(const sf::Texture& texture) {
	this->texture = texture;

	this->sprite.setTexture(this->texture);
}
Image::Image(void) {
}
Image::~Image(void) {
}
void Image::SetPosition(const sf::Vector2f& pos) {
	this->sprite.setPosition(pos);
}
void Image::SetOrigin(const Pivot& pivot) {
	this->sprite.setOrigin(SwitchPivot(pivot, this->GetSize()));
}
void Image::SetOrigin(const Pivot& pivot, sf::Vector2f* offset) {
	this->sprite.setOrigin(SwitchPivotOffset(pivot, this->GetSize(), *offset));
}
sf::Vector2f* Image::GetSize(void) {
	return new sf::Vector2f(this->sprite.getTexture()->getSize().x * this->sprite.getScale().x,
		this->sprite.getTexture()->getSize().y * this->sprite.getScale().y);
}
const sf::Vector2f& Image::GetOrigin(void) const {
	return this->sprite.getOrigin();
}
void Image::UpdateGlobalBounds(void) {
	this->globalBounds = this->sprite.getGlobalBounds();
}
void Image::Draw(void) {
	this->manager->window->draw(this->sprite);
}