#include "CollisionRect.h"

using namespace coll;

bool CollisionRect::IsCollidingWith(CollisionRect& r)
{
	return (this->position.x + this->size.x > r.position.x
			&& this->position.y + this->size.y > r.position.y
		    && r.position.x + r.size.x > this->position.x
			&& r.position.y + r.size.y > this->position.x);
}