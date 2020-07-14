#pragma once

#include <SFML/Graphics.hpp>

namespace coll
{
	class CollisionRect
	{
	public:

		enum class CollisionDirection
		{
			TOP,
			BOTTOM,
			LEFT,
			RIGHT,
			NONE
		};

		sf::Vector2f position;
		sf::Vector2f size;

		bool IsCollidingWith(CollisionRect& r);
		const CollisionDirection& GetCollisionDirection(CollisionRect& r);
	};
}