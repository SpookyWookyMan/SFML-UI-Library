#pragma once

#include <SFML/Graphics.hpp>

class Tile 
{
protected:

	sf::RectangleShape shape;

public:

	Tile(const sf::Vector2f& pos, const unsigned& gridSize);
	Tile(void);
	~Tile(void);

	void Update(void);
	void Draw(sf::RenderTarget& target);

};