#pragma once

#include "TileChunkManager.h"

class Map 
{
public:

	TileChunkManager chunkManager;

	Map(const sf::Texture& tileset);

	void Init(void);	
	void Update(void);
	void Draw(sf::RenderTarget& target);
};