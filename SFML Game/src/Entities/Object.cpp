#include "Object.h"

void Object::SetPosition(const sf::Vector2f& position) 
{
	this->position = position;
	this->sprite.setPosition(this->position);
	this->collisionRect.position = this->position;
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

void Object::Update(void)
{
}
void Object::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Object::BindCollisionRectToObject(void)
{
	sf::Vector2f* size = new sf::Vector2f(this->sprite.getTexture()->getSize().x * this->sprite.getScale().x,
		this->sprite.getTexture()->getSize().y * this->sprite.getScale().y);

	this->collisionRect.size = *size;
	this->collisionRect.position = this->position;

	delete size;
}
