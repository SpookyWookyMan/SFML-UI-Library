#pragma once

#include "TileChunkManager.h"

class Map 
{
public:

	TileChunkManager chunkManager;
	sf::Texture tileset;

	Map(const char* pathToTexture);

	void Init(void);	
	void Update(void);
	void Draw(sf::RenderTarget& target);
};