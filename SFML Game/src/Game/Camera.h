#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Camera
{
public:

	sf::RenderTarget* target;
	sf::View view;
	
	sf::Vector2f position;
	sf::Vector2f size;

	float speed;

	Camera(sf::RenderTarget& target, const sf::Vector2f& position, const sf::Vector2f& size);
	Camera(sf::RenderTarget& target, const sf::Vector2f& position);
	Camera(sf::RenderTarget& target);
	Camera(void);
	~Camera(void);

	void SetRenderTarget(sf::RenderTarget& target);
	void SetCameraPosition(const sf::Vector2f& position);
	void SetCameraSize(const sf::Vector2f& size);
	void SetBounds(const float& upper, const float& lower);

	void MoveToTarget(const sf::Vector2f& target, const float& speed, const float& dt);

private:

	float upperBounds;
	float lowerBounds;

};