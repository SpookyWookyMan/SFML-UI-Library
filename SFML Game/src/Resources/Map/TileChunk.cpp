#include "TileChunk.h"
TileChunk::TileChunk(void) 
{
}
TileChunk::~TileChunk(void) 
{
	for (auto& i : this->tiles) delete i;
	this->tiles.clear();

	delete this->tileset;
}
const sf::Vector2u& TileChunk::GetSize(void) const
{
	return { this->layout.at(0).size(), this->layout.size()  };
}
void TileChunk::GenerateTiles(const sf::Vector2f& position) 
{
	for (auto i = 0; i < layout.size(); i++)
	{
		for (auto j = 0; j < layout.at(0).size(); j++)
		{
			unsigned x = (this->layout.at(i).at(j) - '0') / 10;
			unsigned y = (this->layout.at(i).at(j) - '0') % 10;
			
			bool isEmpty = (x + y) == 0;

			sf::IntRect* intrect = new sf::IntRect(x * this->tileSize, y * this->tileSize, this->tileSize, this->tileSize);
			sf::Vector2f* pos = new sf::Vector2f(this->tileSize * j, this->tileSize * i);
			
			if(!isEmpty) this->tiles.push_back(new Tile(position, this->tileset, intrect)); 

			delete intrect, pos;
		}
	}
}
void TileChunk::DrawChunk(sf::RenderTarget& target) 
{
	for (auto& i : this->tiles) 
	{
		target.draw(i->sprite);
	}
}