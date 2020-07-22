#pragma once

#include "Object.h"

class Player : public Object 
{
	sf::Texture texture; //temporary

public:

	bool isGrounded;    
	bool canMoveRight = true; 
	bool canMoveLeft = true; 

	Player(void);
	~Player(void);

	void Init(void);
	void Events(sf::Event& event);
	void Update(float& deltaTime) override;
	void Draw(sf::RenderTarget& target) override;

};