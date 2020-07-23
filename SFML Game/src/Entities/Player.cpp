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
	this->SetVelocity({ 60.5f, 130.5f });
	this->SetPosition({-40.0f, 500.0f});
	this->sprite.setScale({0.1f, 0.3f});
	this->BindCollisionRectToObject();

	this->startingPosition = this->position;
}

void Player::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded) //fix this mess
		{
			this->position.y -= 0.3f;
			this->SetPosition(this->position);
			this->velocity.y = -75.1f;
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
		this->velocity.y += (velocity.y > 130.5f ? 0.0f : 155.1f) *deltaTime;
		this->position.y += this->velocity.y * deltaTime;
	}

	this->sprite.setPosition(this->position);
	this->BindCollisionRectToObject();
}
void Player::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
void Player::Restart(void) 
{
	this->SetPosition(this->startingPosition);
	this->canMoveLeft = this->canMoveRight = true;
}