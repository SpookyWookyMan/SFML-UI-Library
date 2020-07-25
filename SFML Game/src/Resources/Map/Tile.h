#pragma once

#include "../../Collision/CollisionRect.h"

class Tile 
{
public:

	enum class TileCollType
	{
		COLLISION,
		DECOR,
		DEADLY,
		BOUNCE,
		SELFD
	} collisionType;

	sf::Sprite sprite;

	bool colliding;
	bool collDirs[4];

	CollisionRect::CollisionDirection coldir = CollisionRect::CollisionDirection::NONE;

	CollisionRect collisionRect;

	Tile(const sf::Vector2f& position, sf::Texture* tileset, const sf::IntRect& txtrRect,
		 const TileCollType& collType, const unsigned& tileScale, bool collDirs[]);
	~Tile(void);

	void SetPosition(const sf::Vector2f& position);
	void SetTextureRect(const sf::IntRect& rect);

private:

	sf::Vector2f position;
	sf::Vector2f size;

	void UpdateCollisionBox(void);

};