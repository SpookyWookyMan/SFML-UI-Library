#pragma once

#include "Tile.h"

class TileMap 
{
private:

	unsigned gridSize;
	unsigned layers;

	sf::Vector2u size;
	std::vector<std::vector<std::vector<Tile> > > map;

public:

	TileMap(void);
	~TileMap(void);

	void Update(void);
	void Draw(sf::RenderTarget& target);

};