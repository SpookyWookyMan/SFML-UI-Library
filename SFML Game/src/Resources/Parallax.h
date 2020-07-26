#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.h"
#include <iostream>

class Parallax {
public:

	sf::Sprite sprite;//test
	sf::Texture t;
	
	Player player;

	float speed;
	float deviation = 0.0f;
	unsigned mod = 1;

	bool canMove;

	void Init(Player& player, sf::View& view) {
		if(!this->t.loadFromFile("Res/Textures/Parallax/glacial_mountains.png"))printf("s");
		this->sprite.setTexture(t);
		t.setRepeated(true);

		this->player = player;

		float scly = view.getSize().y / t.getSize().y;
		float sclx = scly;

		sf::Vector2f pos(view.getCenter().x - view.getSize().x, view.getCenter().y + view.getSize().y / 2);
		sf::Vector2f sprdim(this->t.getSize().x *sclx, this->t.getSize().y * scly);

		this->sprite.setOrigin({ 0.0f, sprdim.y });
		this->sprite.setPosition(pos);
		this->sprite.setScale({sclx, scly});
		this->sprite.setTextureRect({0,0, (int)(this->t.getSize().x) ,(int)this->t.getSize().y});

	} //test
	void Update(const float& dt, sf::View& view) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.canMoveLeft) {
			this->deviation += 0.5f * dt;
			this->canMove = true;
			//this->sprite.move(1.f * dt, 0.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.canMoveRight) {
			//this->sprite.move(-1.f * dt, 0.0f);
			this->deviation -= 0.5f * dt;
			this->canMove = true;
		}
		else this->canMove = false;

		//sf::Vector2f pos(this->sprite.getPosition().x + this->deviation, view.getCenter().y + view.getSize().y / 2);
		if(canMove)this->sprite.move(deviation*dt,0);

		sf::Vector2f sprpos(this->sprite.getPosition());
		sf::Vector2f sprdim(this->t.getSize().x * this->sprite.getScale().x,
			this->t.getSize().y * this->sprite.getScale().y);

		if(sprpos.x + sprdim.x < view.getCenter().x + view.getSize().x/2) {
			printf("here\n");
			mod++;
			this->sprite.setTextureRect({ 0,0, (int)(this->t.getSize().x * mod) ,(int)this->t.getSize().y });
		}

	}
	void Draw(sf::RenderTarget& target) {
		target.draw(this->sprite);
	}

private:

};