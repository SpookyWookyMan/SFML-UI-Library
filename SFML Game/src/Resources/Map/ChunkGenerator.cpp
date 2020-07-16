#include "ChunkGenerator.h"

void TileChunkGenerator::DrawChunks(sf::RenderTarget& target) 
{
	for(auto& i : this->tileChunks)
	{
		i.DrawChunk(target);
	}
}