#include "TileMap.h"

TileMap::TileMap(void)
{
	this->gridSize = 50;
	this->size.x = 10;
	this->size.y = 10;
	this->layers = 1;

	this->map.resize(this->size.x);
	for (auto x = 0; x < this->size.x; x++) 
	{
		this->map.push_back(std::vector<std::vector<Tile> >());
		for (auto y = 0; y < this->size.y; y++) 
		{
			this->map[x].resize(this->size.y);
			this->map[x].push_back(std::vector<Tile>());
			for (auto z = 0; z < this->layers; z++) 
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile({ static_cast<float>(x * this->gridSize), 
					static_cast<float>(y * this->gridSize) }, this->gridSize));
			}
		}
	}
}
TileMap::~TileMap(void) 
{
}

void TileMap::Update(void)
{
}

void TileMap::Draw(sf::RenderTarget& target)
{
	for (auto& x : this->map) 
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.Draw(target);
			}
		}
	}
}

