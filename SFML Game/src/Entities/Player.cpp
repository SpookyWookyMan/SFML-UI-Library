#include "Player.h"

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

}
void Player::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded) //fix this mess
		{
			this->position.y -= 0.3f;
			this->SetPosition(this->position);
			this->velocity.y = -0.3f;
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
	}
}
void Player::Update(void) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->position.x += canMoveRight ? this->velocity.x : 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->position.x -= canMoveLeft ? this->velocity.x : 0.0f;
	}

	if (!isGrounded) //fix this mess
	{
		this->velocity.y += (velocity.y > 0.25f) ? 0.0f : 0.0003f;
		this->position.y += this->velocity.y;
	}

	this->sprite.setPosition(this->position);
	this->BindCollisionRectToObject();
}
void Player::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}