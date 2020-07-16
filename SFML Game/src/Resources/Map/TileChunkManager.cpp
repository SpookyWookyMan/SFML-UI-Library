#include "TileChunkManager.h"

TileChunkManager::TileChunkManager(sf::Texture* tileset)
{
	this->tileset = *tileset;
	for (auto& i : this->tileChunks) i.tileset = &this->tileset;
}
TileChunkManager::TileChunkManager(void)
{
}
TileChunkManager ::~TileChunkManager(void)
{
}
void TileChunkManager::AddChunk(const TileChunk& tchunk)
{
	this->tileChunks.push_back(tchunk);
}
void TileChunkManager::DrawChunks(sf::RenderTarget& target)
{
	for(auto& i : this->tileChunks) i.DrawChunk(target);
}