#include "Map.h"

//TODO:
//	-Fix messed up tileScale thing

Map::Map(const char* pathToTexture) {
	if (!this->tileset.loadFromFile(pathToTexture)) printf("Failed to load tileset\n");
	else printf("Tilset loaded\n");
}

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

	TileChunk* initialChunk = new TileChunk();

	initialChunk->tileset = &this->tileset;
	initialChunk->player = player;
	initialChunk->layout = chunkManager.layouts.at(0);
	initialChunk->GenerateTiles(chunkManager.tileSize, chunkManager.tileScale);
	initialChunk->position = { -70.0f, 500.0f };
	initialChunk->UpdatePosition();
	initialChunk->hasGenerated = true;

	TileChunk* initialChunk2 = new TileChunk();

	initialChunk2->tileset = &this->tileset;
	initialChunk2->player = player;
	initialChunk2->layout = chunkManager.layouts.at(0);
	initialChunk2->GenerateTiles(chunkManager.tileSize, chunkManager.tileScale);
	initialChunk2->position = { 15.0f + chunkManager.tileSize * 2, 500.0f };
	initialChunk2->UpdatePosition();

	this->chunkManager.generatedChunks.push_back(initialChunk);
	this->chunkManager.generatedChunks.push_back(initialChunk2);
}
void Map::Update(const float& dt) {
	for (auto& chunk : chunkManager.generatedChunks) { 
		chunk->CheckPlayerCollision();
		chunk->Update(dt);
	}
}
void Map::Draw(sf::RenderTarget& target) {
	this->chunkManager.DrawChunks(target);
}