#include "CollisionRect.h"

bool CollisionRect::IsCollidingWith(CollisionRect& r) {
	return (this->position.x + this->size.x > r.position.x
			&& this->position.y + this->size.y > r.position.y
		    && r.position.x + r.size.x > this->position.x
			&& r.position.y + r.size.y > this->position.y);
}
const CollisionRect::CollisionDirection& CollisionRect::GetCollisionDirection(CollisionRect& r) {
	if (this->IsCollidingWith(r)) {
		if (this->position.y < r.position.y) return CollisionDirection::TOP;
		else if (this->position.y > r.position.y + r.size.y - this->size.y / 5) return CollisionDirection::BOTTOM; //change this to this->position.y > r.position.y + r.size.y + this->size.y / 6
		else if (this->position.x < r.position.x) return CollisionDirection::LEFT;
		else if (this->position.x > r.position.x + r.size.x - this->size.x) return CollisionDirection::RIGHT;
	}
	return CollisionDirection::NONE;
}