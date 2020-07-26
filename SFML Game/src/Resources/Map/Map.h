#pragma once

#include "TileChunkManager.h"
#include "BackgroundManager.h"

class Map 
{
public:

	TileChunkManager chunkManager;
	BackgroundManager parallax;

	sf::Texture tileset;

	Map(const char* pathToTexture);

	void Init(Player* player, sf::View&view);
	void Update(const float& dt);
	void Draw(sf::RenderTarget& target);
};