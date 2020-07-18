#pragma once

#include "../../Collision/CollisionRect.h"

class Tile 
{
public:

	enum class TileCollType
	{
		COLLISION,
		DECOR
	} collisionType;

	sf::Sprite sprite;

	//testing
	bool colliding = false;
	CollisionRect::CollisionDirection coldir = CollisionRect::CollisionDirection::NONE;
	//testing^

	CollisionRect collisionRect;

	Tile(const sf::Vector2f& position, sf::Texture* tileset, sf::IntRect* txtrRect, 
		 const TileCollType& collType, const unsigned& tileScale);
	~Tile(void);

	void SetPosition(const sf::Vector2f& position);
	void SetTextureRect(const sf::IntRect& rect);

private:

	sf::Vector2f position;
	sf::Vector2f size;

	void UpdateCollisionBox(void);

};