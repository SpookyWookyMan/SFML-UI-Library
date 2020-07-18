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
			unsigned collType = this->layout.at(i).at(j) / 0x64;
			unsigned tileLoc = this->layout.at(i).at(j) % 0x64;

			unsigned x = tileLoc / 0xF;
			unsigned y = tileLoc % 0xF;

			bool isEmpty = (x + y) < 0x1;
			std::cout << isEmpty << "\n";

			Tile::TileCollType tileCollType = collType == 0x1 ? Tile::TileCollType::COLLISION : Tile::TileCollType::DECOR;
			//if (collType == 0x1) tileCollType = Tile::TileCollType::COLLISION;
			//else if (collType == 0x2) tileCollType = Tile::TileCollType::DECOR;

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
		target.draw(i->sprite);
	}
}
void TileChunk::CheckPlayerCollision() 
{
	for (auto& tile : this->tiles) 
	{
		using CLD = CollisionRect::CollisionDirection;

		if (tile->collisionType == Tile::TileCollType::COLLISION)
		{
			if (tile->collisionRect.IsCollidingWith(player->collisionRect)) 
			{
				CLD colDir = player->collisionRect.GetCollisionDirection(tile->collisionRect);

				if (colDir == CLD::RIGHT || colDir == CLD::LEFT)
					printf("sides\n");
				tile->sprite.setColor(sf::Color::Red);
				tile->coldir = colDir;
				tile->colliding = true;
				switch (colDir)
				{
				    case CLD::TOP: player->isGrounded = true; break;
					case CLD::BOTTOM: break;
					case CLD::LEFT: player->canMoveRight = false; break;
					case CLD::RIGHT: player->canMoveLeft = false; break;
				    default: break;
				}
			}
			if (tile->colliding && !tile->collisionRect.IsCollidingWith(player->collisionRect))
			{
				switch (tile->coldir)
				{
					case CLD::TOP: player->isGrounded = false; break;
					case CLD::BOTTOM: break;
					case CLD::LEFT: player->canMoveRight = true; break;
					case CLD::RIGHT: player->canMoveLeft = true; break;
					default: break;
				}
				tile->sprite.setColor(sf::Color::White);
				tile->coldir = CLD::NONE;
				tile->colliding = false;
			}

		} else continue;
	}
}