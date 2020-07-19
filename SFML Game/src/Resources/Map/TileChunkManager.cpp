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
	printf("destroyed\n");
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
		{
			this->generatedChunks.at(i)->DrawChunk(target);
			if ((this->generatedChunks.at(i)->position.x + this->generatedChunks.at(i)->GetSize().x) < (target.getView().getCenter().x + target.getView().getSize().x / 2))
			{
				this->GenerateNewChunk(target.getView());
			}
		}
		else
		{ 
			//delete this->generatedChunks.at(i);
			//this->generatedChunks.erase(this->generatedChunks.begin() + i + 1);
		}
	}
}
void TileChunkManager::GenerateNewChunk(const sf::View& view) 
{
	unsigned index = 0;// rand() % (this->tileChunks.size() - 1) + 0;

	this->generatedChunks.push_back(&this->tileChunks.at(1));

	this->generatedChunks.at(this->generatedChunks.size() - 1)->position.x =
		(view.getCenter().x + view.getSize().x / 2) + this->generatedChunks.at(0)->tileSize;
	this->generatedChunks.at(this->generatedChunks.size() - 1)->position.y =
		(view.getCenter().y + view.getSize().y / 2) - this->generatedChunks.at(this->generatedChunks.size() - 1)->GetSize().y;
	
	std::cout << this->generatedChunks.size() << "\n";
	std::cout << "View x is: " << view.getCenter().x + view.getSize().x / 2 << "\n";
	std::cout << "View y is: " << view.getCenter().y + view.getSize().y / 2 << "\n";
	std::cout << "This tileChunk's x is: " << this->generatedChunks.at(this->generatedChunks.size() - 1)->position.x << "\n";
	std::cout << "This tileChunk's y is: " << this->generatedChunks.at(this->generatedChunks.size() - 1)->position.y << "\n\n";
	std::cout << "This tileChunk's texture is: " << this->generatedChunks.at(this->generatedChunks.size() - 1)->tileset << "\n";
}