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
							{147, 200, 147, 147, 147},
							{148, 200, 148, 200, 200},
							{148, 148, 148, 148, 148},
							{200, 200, 148, 200, 148},
							{149, 149, 149, 200, 149}
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