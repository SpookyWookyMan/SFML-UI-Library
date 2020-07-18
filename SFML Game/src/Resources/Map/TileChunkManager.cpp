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
	for (size_t i = 0; i < this->generatedChunks.size(); i++)
	{
		if (this->generatedChunks.at(i)->IsWithinView(target.getView()))
			this->generatedChunks.at(i)->DrawChunk(target);
		else
		{ 
			this->generatedChunks.erase(this->generatedChunks.begin() + i + 1);
			this->GenerateNewChunk(target.getView());
			//unsigned index = rand() % this->tileChunks.size() + 0;
			//this->generatedChunks.push_back(this->tileChunks.at(index));
			//this->generatedChunks.at(this->generatedChunks.size() - 1).position.x = 
			//	(target.getView().getCenter().x + target.getView().getSize().x / 2) + this->generatedChunks.at(0).tileSize;
			//this->generatedChunks.at(this->generatedChunks.size() - 1).position.y =
			//	(target.getView().getCenter().y + target.getView().getSize().y / 2) - this->generatedChunks.at(this->generatedChunks.size() - 1).GetSize().y;
		}
	}
}
void TileChunkManager::GenerateNewChunk(const sf::View& view) 
{
	unsigned index = rand() % this->tileChunks.size() + 0;

	this->generatedChunks.push_back(&this->tileChunks.at(index));
	this->generatedChunks.at(this->generatedChunks.size() - 1)->position.x =
		(view.getCenter().x + view.getSize().x / 2) + this->generatedChunks.at(0)->tileSize; //change tileScale later
	this->generatedChunks.at(this->generatedChunks.size() - 1)->position.y =
		(view.getCenter().y + view.getSize().y / 2) - this->generatedChunks.at(this->generatedChunks.size() - 1)->GetSize().y;
}