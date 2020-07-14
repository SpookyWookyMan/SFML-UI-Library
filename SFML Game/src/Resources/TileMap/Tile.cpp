#include "Tile.h"

Tile::Tile(const sf::Vector2f& pos, const unsigned& gridSize)
{
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(pos);
}
Tile::Tile(void) 
{
}
Tile::~Tile(void) 
{
}

void Tile::Update(void)
{

}
void Tile::Draw(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
