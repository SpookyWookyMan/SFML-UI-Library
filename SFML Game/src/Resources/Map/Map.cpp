#include "Map.h"

Map::Map(const sf::Texture& tileset) 
{
	this->chunkManager.tileset = tileset;
}
void Map::Init(void) 
{
}
void Map::Update(void) 
{
}
void Map::Draw(sf::RenderTarget& target) 
{
	this->chunkManager.DrawChunks(target);
}