#include "Map.h"

//TODO:
//	-Fix messed up tileScale thing

Map::Map(const char* pathToTexture) {
	if (!this->tileset.loadFromFile(pathToTexture)) printf("Failed to load tileset\n");
	else printf("Tilset loaded\n");
}

TileChunk testchunk;
TileChunk testchunk2;
TileChunk testchunk3;
TileChunk testchunk4;

void Map::Init(Player* player) {
	this->chunkManager.tileset = this->tileset;
	this->chunkManager.player = player;
	this->chunkManager.tileSize = 8;
	this->chunkManager.tileScale = 2;

	this->chunkManager.layouts = 
	{
		{
			{200, 200, 141, 147, 147},
			{141, 200, 143, 139, 200},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 200, 149}
		},
		{
			{144, 200, 141, 147, 147},
			{141, 200, 143, 139, 200},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 200, 149}
		},
		{
			{141, 200, 141, 147, 147},
			{141, 200, 143, 139, 200},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 200, 149}
		},
		{
			{148, 200, 141, 147, 147},
			{141, 200, 143, 139, 200},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 200, 149}
		}
	};
}
void Map::Update(void) {
	for (auto& chunk : chunkManager.generatedChunks) { chunk->CheckPlayerCollision(); }
}
void Map::Draw(sf::RenderTarget& target) {
	this->chunkManager.DrawChunks(target);
}