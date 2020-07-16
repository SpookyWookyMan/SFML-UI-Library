#pragma once

#include <iostream>
#include "TileChunk.h"

class TileChunkGenerator 
{
public:

	std::vector<TileChunk> tileChunks;
	
	sf::Texture tileset;

	void DrawChunks(sf::RenderTarget& target);
	
};