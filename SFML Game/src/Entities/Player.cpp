#include "Player.h"
#include <iostream>

Player::Player(void)
{
	this->texture.loadFromFile("Res/Textures/default.png"); //temporary
	this->sprite.setTexture(texture);
}
Player::~Player(void) 
{

}

void Player::Init(void) 
{
	this->SetVelocity({ 16.5f, 0.05f });
	this->SetPosition({20.0f, 420.0f});
	this->sprite.setScale({0.1f, 0.1f});
	this->BindCollisionRectToObject();
}
void Player::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded) //fix this mess
		{
			this->position.y -= 0.3f;
			this->SetPosition(this->position);
			this->velocity.y = -0.02f;
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
	}
}
void Player::Update(float& deltaTime) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->position.x += (canMoveRight ? this->velocity.x : 0.0f) *deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->position.x -= (canMoveLeft ? this->velocity.x : 0.0f) *deltaTime;
	}

	if (!isGrounded)
	{
		//printf("here\n");
		this->velocity.y += (velocity.y > 0.05f ? 0.0f : 0.04f) *deltaTime;
		this->position.y += this->velocity.y;
	}

	this->sprite.setPosition(this->position);
	this->BindCollisionRectToObject();
}
void Player::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}