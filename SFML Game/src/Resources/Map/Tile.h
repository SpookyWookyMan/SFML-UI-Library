#pragma once

#include "../../Collision/CollisionRect.h"

class Tile 
{
public:

	enum class TileCollType //check what to do with this
	{
		COLLISION,
		DECOR
	} collisionType;

	sf::Sprite sprite;

	CollisionRect collisionRect;

	Tile(const sf::Vector2f& position, sf::Texture* tileset, sf::IntRect* txtrRect, const TileCollType& collType);
	~Tile(void);

	void SetPosition(const sf::Vector2f& position);
	void SetTextureRect(const sf::IntRect& rect);

private:

	sf::Vector2f position;
	sf::Vector2f size;

	void UpdateCollisionBox(void);

};