#include "Map.h"

Map::Map(const char* pathToTexture) 
{
	if (!this->tileset.loadFromFile(pathToTexture)) printf("Failed to load tileset\n");
	else printf("Tilset loaded\n");
}

TileChunk testchunk;
void Map::Init(void) 
{
	this->chunkManager.tileset = this->tileset;
	
	testchunk.tileset = &this->chunkManager.tileset;
	testchunk.tileSize = 8;
	testchunk.position = {100.0f, 100.0f};
	testchunk.layout = {
							{47, 00, 47, 47, 47},
							{48, 00, 48, 00, 00},
							{48, 48, 48, 48, 48},
							{00, 00, 48, 00, 48},
							{49, 49, 49, 00, 49}
					   };
	testchunk.GenerateTiles();
	this->chunkManager.AddChunk(testchunk);
}
void Map::Update(void) 
{
}
void Map::Draw(sf::RenderTarget& target) 
{
	this->chunkManager.DrawChunks(target);
}