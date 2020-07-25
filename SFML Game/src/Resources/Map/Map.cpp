#include "Map.h"

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
			{141, 441, 441, 447, 147},
			{141, 141, 143, 139, 141},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 141, 149}
		},
		{
			{144, 200, 141, 147, 147},
			{141, 200, 143, 139, 200},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 200, 149}
		},
		{
			{141, 200, 141, 200, 147},
			{141, 200, 143, 200, 200},
			{142, 200, 145, 200, 148},
			{167, 200, 143, 145, 148},
			{145, 144, 144, 145, 149}
		},
		{
			{148, 200, 141, 147, 147},
			{141, 200, 143, 139, 200},
			{142, 148, 145, 148, 148},
			{167, 134, 143, 200, 148},
			{145, 144, 144, 200, 149}
		},
		{
			{148, 200, 141, 200, 147, 200, 147, 200, 147},
			{141, 200, 143, 200, 147, 200, 147, 200, 147},
			{142, 148, 145, 148, 148, 147, 147, 147, 147},
			{167, 134, 143, 147, 148, 147, 147, 147, 147},
			{145, 144, 144, 147, 149, 147, 147, 147, 147}
		}
	};

	TileChunk* initialChunk = new TileChunk();

	initialChunk->tileset = &this->tileset;
	initialChunk->player = player;
	initialChunk->layout = chunkManager.layouts.at(0);
	initialChunk->GenerateTiles(chunkManager.tileSize, chunkManager.tileScale);
	initialChunk->position = { -70.0f, 520.0f };
	initialChunk->UpdatePosition();
	initialChunk->hasGenerated = true;
	initialChunk->destructionTime = (chunkManager.tileSize * chunkManager.tileScale / chunkManager.player->velocity.x)
		* initialChunk->GetElementSize().x;

	TileChunk* initialChunk2 = new TileChunk();

	initialChunk2->tileset = &this->tileset;
	initialChunk2->player = player;
	initialChunk2->layout = chunkManager.layouts.at(0);
	initialChunk2->GenerateTiles(chunkManager.tileSize, chunkManager.tileScale);
	initialChunk2->position = { 15.0f + chunkManager.tileSize * 2, 520.0f };
	initialChunk2->UpdatePosition();
	initialChunk2->destructionTime = (chunkManager.tileSize * chunkManager.tileScale / chunkManager.player->velocity.x)
		* initialChunk2->GetElementSize().x;

	this->chunkManager.generatedChunks.push_back(initialChunk);
	this->chunkManager.generatedChunks.push_back(initialChunk2);

	std::cout << sizeof(sf::Clock) << "\n";
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