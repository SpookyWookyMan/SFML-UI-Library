#pragma once

#include <iostream>
#include "TileChunk.h"

class TileChunkManager 
{
public:

	std::vector<std::vector<std::vector<unsigned> > > layouts;
	std::vector<TileChunk*> generatedChunks;


	unsigned tileSize;
	unsigned tileScale;

	sf::Texture tileset;

	Player* player;

	TileChunkManager(sf::Texture* tileset);
	TileChunkManager(void);
	~TileChunkManager(void);

	void DrawChunks(sf::RenderTarget& target);
	void GenerateNewChunk(const sf::View& view);
};