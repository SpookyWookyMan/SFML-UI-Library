#pragma once

#include <iostream>
#include "Tile.h"

class TileChunk 
{
public:

	unsigned tileSize;

	sf::Texture* tileset;

	std::vector<std::vector<char> > layout;
	std::vector<Tile*> tiles;

	TileChunk(void);
	~TileChunk(void);

	const sf::Vector2u& GetSize(void) const;
	void GenerateTiles(const sf::Vector2f& position);
	void DrawChunk(sf::RenderTarget& target);
};