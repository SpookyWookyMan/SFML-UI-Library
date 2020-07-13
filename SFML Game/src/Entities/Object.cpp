#include "Object.h"

void Object::SetPosition(const sf::Vector2f& position) 
{
	this->position = position;
}
void Object::SetVelocity(const sf::Vector2f& velocity) 
{
	this->velocity = velocity;
}
void Object::SetActive(const bool& active)
{
	this->isActive = active;
}
const bool& Object::IsActive(void) const 
{
	return this->isActive;
}