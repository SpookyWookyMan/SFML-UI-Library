#include "TileChunkManager.h"

TileChunkManager::TileChunkManager(sf::Texture* tileset) {
	this->tileset = *tileset;
}
TileChunkManager::TileChunkManager(void)
	:player{nullptr}, tileSize{0}, tileScale{0} {
}
TileChunkManager ::~TileChunkManager(void) {
}
void TileChunkManager::DrawChunks(sf::RenderTarget& target) {
	if (this->generatedChunks.size() < 1) this->GenerateNewChunk(target.getView());
	for (size_t i = 0; i < this->generatedChunks.size(); i++) {
		if (this->generatedChunks.at(i)->IsWithinView(target.getView())) {
			this->generatedChunks.at(i)->DrawChunk(target);
			if ((this->generatedChunks.at(i)->position.x + this->generatedChunks.at(i)->GetSize().x) < (target.getView().getCenter().x + target.getView().getSize().x / 2)
				&& !this->generatedChunks.at(i)->hasGenerated) {
				this->GenerateNewChunk(target.getView());
				this->generatedChunks.at(i)->hasGenerated = true;
			}
		}
		else { 
			//delete this->generatedChunks.at(i);
			//this->generatedChunks.erase(this->generatedChunks.begin() + i);
		}
	}
}
void TileChunkManager::GenerateNewChunk(const sf::View& view) {
	unsigned index = rand() % (this->layouts.size() - 1) + 1;

	TileChunk* tchunk = new TileChunk();
	tchunk->index = index;
	tchunk->tileset = &this->tileset;
	tchunk->player = this->player;
	tchunk->layout = this->layouts.at(index);
	tchunk->GenerateTiles(this->tileSize, this->tileScale);
	tchunk->position = { (view.getCenter().x + view.getSize().x / 2) + this->tileSize * this->tileScale * 2, 
		(view.getCenter().y + view.getSize().y / 2) - tchunk->GetSize().y };

	tchunk->UpdatePosition();
	tchunk->destructionTime = (this->tileSize * this->tileScale / this->player->velocity.x)
		* tchunk->GetElementSize().x;

	this->generatedChunks.push_back(new TileChunk(*tchunk));

	delete tchunk;
}