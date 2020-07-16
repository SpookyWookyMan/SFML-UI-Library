#include "TileChunk.h"

TileChunk::TileChunk(void) 
{
}
TileChunk::~TileChunk(void) 
{
	for (auto& i : this->tiles) i = nullptr;
	this->tiles.clear();
}
const sf::Vector2u& TileChunk::GetSize(void) const
{
	return { static_cast<unsigned>(this->layout.at(0).size()), 
			 static_cast<unsigned>(this->layout.size())  };
}
void TileChunk::GenerateTiles() 
{
	for (auto i = 0; i < layout.size(); i++)
	{
		for (auto j = 0; j < layout.at(0).size(); j++)
		{
			unsigned collType = this->layout.at(i).at(j) / 100;
			unsigned tileLoc = this->layout.at(i).at(j) % 100;

			unsigned x = tileLoc / 10;
			unsigned y = tileLoc % 10;

			bool isEmpty = (x + y) == 0;

			Tile::TileCollType tileCollType = collType == 1 ? Tile::TileCollType::COLLISION : Tile::TileCollType::DECOR;

			sf::IntRect* intrect = new sf::IntRect(x * this->tileSize, y * this->tileSize, this->tileSize, this->tileSize);
			sf::Vector2f* pos = new sf::Vector2f(this->position.x + (this->tileSize * j), this->position.y + (this->tileSize * i));
			
			if(!isEmpty) this->tiles.push_back(new Tile(*pos, this->tileset, intrect, tileCollType)); 

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
CollisionRect::CollisionDirection TileChunk::CheckCollision(CollisionRect& rect) const
{
	for (auto& i : this->tiles) 
	{
		if (i->collisionRect.GetCollisionDirection(rect) != CollisionRect::CollisionDirection::NONE)
		{
			switch (i->collisionRect.GetCollisionDirection(rect)) //forgive me
			{
			case CollisionRect::CollisionDirection::TOP: 
				return CollisionRect::CollisionDirection::BOTTOM; break;
			case CollisionRect::CollisionDirection::BOTTOM:
				return CollisionRect::CollisionDirection::TOP; break;
			case CollisionRect::CollisionDirection::LEFT:
				return CollisionRect::CollisionDirection::RIGHT; break;
			case CollisionRect::CollisionDirection::RIGHT:
				return CollisionRect::CollisionDirection::LEFT; break;
			default: return CollisionRect::CollisionDirection::NONE; break;
			}
		} 
		else continue;
	}
	return CollisionRect::CollisionDirection::NONE;
}