#pragma once

#include <SFML/Graphics.hpp>

class CollisionRect
{
public:

	enum class CollisionDirection
	{
		TOP    =  1,
		BOTTOM = -1,
		LEFT   =  2,
		RIGHT  = -2,
		NONE   =  0
	};

	sf::Vector2f position;
	sf::Vector2f size;

	bool IsCollidingWith(CollisionRect& r);
	const CollisionDirection& GetCollisionDirection(CollisionRect& r);
};