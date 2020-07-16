#include "Tile.h"
#include <iostream>

Tile::Tile(const sf::Vector2f& position, sf::Texture* tileset, sf::IntRect* txtrRect, const TileCollType& collType)
{
	this->sprite.setTexture(*tileset);
	this->SetPosition(position);
	this->SetTextureRect(*txtrRect);

	this->collisionType  = collType;
}
Tile::~Tile(void) 
{
}

void Tile::SetPosition(const sf::Vector2f& position) 
{
	this->position = position;
	this->UpdateCollisionBox();
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