#pragma once

#include <SFML/Graphics.hpp>

namespace coll
{
	class CollisionRect
	{
	public:

		sf::Vector2f position;
		sf::Vector2f size;

		bool IsCollidingWith(CollisionRect& r);
	};
}