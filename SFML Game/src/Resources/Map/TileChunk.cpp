#include "TileChunk.h"
TileChunk::TileChunk(void) 
{
}
TileChunk::~TileChunk(void) 
{
	for (auto& i : this->tiles) i = nullptr;
	this->tiles.clear();

	//delete this->tileset;
}
const sf::Vector2u& TileChunk::GetSize(void) const
{
	return { static_cast<unsigned>(this->layout.at(0).size()), 
			 static_cast<unsigned>(this->layout.size())  };
}
void TileChunk::GenerateTiles() 
{
	std::cout << this->tileset << "\n";

	for (auto i = 0; i < layout.size(); i++)
	{
		for (auto j = 0; j < layout.at(0).size(); j++)
		{
			unsigned x = this->layout.at(i).at(j) / 10;
			unsigned y = this->layout.at(i).at(j) % 10;
			
			std::cout << this->layout.at(i).at(1) << "\n";

			bool isEmpty = (x + y) == 0;

			sf::IntRect* intrect = new sf::IntRect(x * this->tileSize, y * this->tileSize, this->tileSize, this->tileSize);
			sf::Vector2f* pos = new sf::Vector2f(this->position.x + (this->tileSize * j), this->position.y + (this->tileSize * i));
			std::cout << this->tileset << "\n";
			if(!isEmpty) this->tiles.push_back(new Tile(*pos, this->tileset, intrect)); 

			delete intrect, pos;
		}
	}
}
void TileChunk::DrawChunk(sf::RenderTarget& target) 
{
	for (auto& i : this->tiles) 
	{
		std::cout << i->sprite.getTexture();
		target.draw(i->sprite);
	}
}