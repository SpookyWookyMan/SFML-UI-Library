#include "Tile.h"

Tile::Tile(const sf::Vector2f& position, sf::Texture* tileset, sf::IntRect* txtrRect)
{
	this->SetPosition(position);
	this->SetTexture(*tileset);
	this->SetTextureRect(*txtrRect);

	this->UpdateCollisionBox();
}
Tile::~Tile(void) 
{
}

void Tile::SetPosition(const sf::Vector2f& position) 
{
	this->position = position;
	this->UpdateCollisionBox();
}
void Tile::SetTexture(const sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}
void Tile::SetTextureRect(const sf::IntRect& rect)
{
	this->sprite.setTextureRect(rect);
}
void Tile::UpdateCollisionBox(void) 
{
	sf::Vector2f* size = new sf::Vector2f(this->sprite.getTexture()->getSize().x * this->sprite.getScale().x,
										  this->sprite.getTexture()->getSize().y * this->sprite.getScale().y);

	this->sprite.setPosition(this->position);
	this->collisionRect.position = this->position;
	this->collisionRect.size = *size;

	delete size;
}