#pragma once

#include "..\Collision\CollisionRect.h"

class Object 
{
public:

	//sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f velocity;

	coll::CollisionRect collisionRect;

	void SetPosition(const sf::Vector2f& position);
	void SetVelocity(const sf::Vector2f& velocity);
	void SetActive(const bool& active);
	
	const bool& IsActive(void) const;

	//virtual void Update(void) = 0;
	//virtual void Draw(void) = 0;

private:

	bool isActive = true;

};