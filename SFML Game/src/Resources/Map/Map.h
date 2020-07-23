#pragma once

#include "TileChunkManager.h"

class Map 
{
public:

	TileChunkManager chunkManager;
	sf::Texture tileset;

	Map(const char* pathToTexture);

	void Init(Player* player);	
	void Update(const float& dt);
	void Draw(sf::RenderTarget& target);
};