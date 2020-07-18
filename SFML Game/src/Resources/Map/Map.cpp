#include "Map.h"

//TODO:
//	-Fix messed up tileScale thing

Map::Map(const char* pathToTexture) 
{
	if (!this->tileset.loadFromFile(pathToTexture)) printf("Failed to load tileset\n");
	else printf("Tilset loaded\n");
}

TileChunk testchunk;
void Map::Init(Player* player) 
{
	this->chunkManager.tileset = this->tileset;
	
	testchunk.tileset = &this->chunkManager.tileset;
	testchunk.position = { 15.0f, 500.0f };
	testchunk.layout = {
							{143, 200, 141, 147, 147},
							{141, 200, 143, 139, 200},
							{142, 148, 145, 148, 148},
							{167, 134, 143, 200, 148},
							{145, 144, 144, 200, 149}
					   };
	testchunk.GenerateTiles(8, 2);
	this->chunkManager.AddChunk(testchunk);
	this->chunkManager.generatedChunks.push_back(&this->chunkManager.tileChunks.at(0));

	for (auto& chunk : chunkManager.tileChunks) chunk.player = player;
}
void Map::Update(void) 
{
	for (auto& chunk : chunkManager.tileChunks) { chunk.CheckPlayerCollision(); }
}
void Map::Draw(sf::RenderTarget& target) 
{
	this->chunkManager.DrawChunks(target);
}