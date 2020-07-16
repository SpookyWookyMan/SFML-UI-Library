#include "TileChunk.h"

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
			unsigned* x = new unsigned((this->layout.at(i).at(j) - '0') / 10);
			unsigned* y = new unsigned((this->layout.at(i).at(j) - '0') % 10);
			
			bool* isEmpty = new bool((*x + *y) == 0);

			sf::IntRect* intrect = new sf::IntRect(*x * this->tileSize, *y * this->tileSize, this->tileSize, this->tileSize);
			sf::Vector2f* pos = new sf::Vector2f(this->tileSize * j, this->tileSize * i);
			
			if(!isEmpty) this->tiles.push_back(new Tile(position, this->tileset, intrect)); 

			delete x , y, isEmpty, intrect, pos, isEmpty;
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