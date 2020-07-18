#pragma once

#include <iostream>
#include "TileChunk.h"

class TileChunkManager 
{
public:

	std::vector<TileChunk> tileChunks;
	std::vector<TileChunk*> generatedChunks;

	sf::Texture tileset;

	TileChunkManager(sf::Texture* tileset);
	TileChunkManager(void);
	~TileChunkManager(void);

	void AddChunk(const TileChunk& tchunk);
	void DrawChunks(sf::RenderTarget& target);
	void GenerateNewChunk(const sf::View& view);
};