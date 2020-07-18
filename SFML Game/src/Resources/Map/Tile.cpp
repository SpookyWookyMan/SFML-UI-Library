#include "Tile.h"
#include <iostream>

Tile::Tile(const sf::Vector2f& position, sf::Texture* tileset, sf::IntRect* txtrRect, const TileCollType& collType
, const unsigned& tileScale)
{
	this->sprite.setTexture(*tileset);
	this->sprite.setScale({ static_cast<float>(tileScale), 
					        static_cast<float>(tileScale)});
	this->SetPosition(position);
	this->SetTextureRect(*txtrRect);

	this->collisionType  = collType;
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
void Tile::SetTextureRect(const sf::IntRect& rect)
{
	this->sprite.setTextureRect(rect);
}
void Tile::UpdateCollisionBox(void) 
{
	sf::Vector2f* size = new sf::Vector2f(this->sprite.getTextureRect().width,
						   				  this->sprite.getTextureRect().height);
	this->sprite.setPosition(this->position);
	this->collisionRect.size = *size;
	this->collisionRect.position = this->position;
	
	delete size;
}