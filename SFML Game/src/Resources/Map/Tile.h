#pragma once

#include "../../Collision/CollisionRect.h"

class Tile 
{
public:

	enum class TileType 
	{
		COLLISION,
		DECOR
	};

	sf::Sprite sprite;

	coll::CollisionRect collisionRect;

	Tile(const sf::Vector2f& position, sf::Texture* tileset, sf::IntRect* txtrRect);
	~Tile(void);

	void SetPosition(const sf::Vector2f& position);
	void SetTexture(const sf::Texture& texture);
	void SetTextureRect(const sf::IntRect& rect);

private:

	sf::Vector2f position;
	sf::Vector2f size;

	void UpdateCollisionBox(void);

};