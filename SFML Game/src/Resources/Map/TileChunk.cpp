#include "TileChunk.h"

TileChunk::TileChunk(void) 
	:hasGenerated{false}, player{nullptr}, tileSize{0}, tileScale{0},
	tileset{nullptr} {
}
TileChunk::TileChunk(const TileChunk& tchunk) {
	this->tileSize = tchunk.tileSize;
	this->tileScale = tchunk.tileScale;
	this->layout = tchunk.layout;
	this->player = tchunk.player;
	this->tiles = tchunk.tiles;
	this->tileset = tchunk.tileset;
	this->position = tchunk.position;
	this->hasGenerated = tchunk.hasGenerated;
}
TileChunk::~TileChunk(void) {
	for (auto& i : this->tiles) i = nullptr;
	this->tiles.clear();
}
TileChunk& TileChunk::operator=(const TileChunk& tchunk) {
	if (this != &tchunk) {
		this->tileSize = tchunk.tileSize;
		this->tileScale = tchunk.tileScale;
		this->layout = tchunk.layout;
		this->player = tchunk.player;
		this->tiles = tchunk.tiles;
		this->tileset = tchunk.tileset;
		this->position = tchunk.position;
		this->hasGenerated = tchunk.hasGenerated;
	}
	return *this;
}
const sf::Vector2u& TileChunk::GetElementSize(void) const {
	return { static_cast<unsigned>(this->layout.at(0).size()), 
			 static_cast<unsigned>(this->layout.size()) };
}
const sf::Vector2f& TileChunk::GetSize(void) const {
	return { static_cast<float>(this->layout.at(0).size() * this->tileSize * this->tileScale),
			 static_cast<float>(this->layout.size() * this->tileSize * this->tileScale) };
}
void TileChunk::GenerateTiles(const unsigned& tileSize, const unsigned& tileScale) {
	this->tileSize = tileSize;
	this->tileScale = tileScale;

	for (size_t i = 0; i < layout.size(); i++) {
		for (size_t j = 0; j < layout.at(0).size(); j++) {
			unsigned collType = this->layout.at(i).at(j) / 0x64;
			unsigned tileLoc = this->layout.at(i).at(j) % 0x64;

			unsigned x = tileLoc / 0xA;
			unsigned y = tileLoc % 0xA;

			bool isEmpty = (x + y) < 0x1;

			Tile::TileCollType tileCollType = collType == 0x1 ? Tile::TileCollType::COLLISION : Tile::TileCollType::DECOR;

			sf::IntRect* intrect = new sf::IntRect(x * this->tileSize, y * this->tileSize, this->tileSize, this->tileSize);
			sf::Vector2f* pos = new sf::Vector2f(this->position.x + (this->tileSize * j * tileScale), this->position.y + (this->tileSize * i * tileScale));
			
			if(!isEmpty) this->tiles.push_back(new Tile(*pos, this->tileset, intrect, tileCollType, tileScale)); 

			delete intrect, pos;
		}
	}
}
void TileChunk::DrawChunk(sf::RenderTarget& target) {
	for (auto& i : this->tiles) {
		target.draw(i->sprite);
	}
}
void TileChunk::CheckPlayerCollision() {
	if (this->IsWithinBounds(this->player->collisionRect)) {
		for (auto& tile : this->tiles) {
			using CLD = CollisionRect::CollisionDirection;

			if (tile->collisionType == Tile::TileCollType::COLLISION) {
				if (tile->collisionRect.IsCollidingWith(player->collisionRect)) {
					CLD colDir = player->collisionRect.GetCollisionDirection(tile->collisionRect);

					tile->sprite.setColor(sf::Color::Red);
					tile->coldir = colDir;
					tile->colliding = true;
					switch (colDir) {
					case CLD::TOP: player->isGrounded = true; break;
					case CLD::BOTTOM: break;
					case CLD::LEFT: player->canMoveRight = false; break;
					case CLD::RIGHT: player->canMoveLeft = false; break;
					default: break;
					}
				}
				if (tile->colliding && !tile->collisionRect.IsCollidingWith(player->collisionRect)) {
					switch (tile->coldir) {
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

			}
			else continue;
		}
	}
}
void TileChunk::UpdatePosition(void) 
{
	std::vector<sf::Vector2f*>* vec = new std::vector<sf::Vector2f*>();

	for (size_t i = 0; i < layout.size(); i++) {
		for (size_t j = 0; j < layout.at(0).size(); j++) {
			sf::Vector2f* pos = new sf::Vector2f(this->position.x + (this->tileSize * j * tileScale), this->position.y + (this->tileSize * i * tileScale));
			
			unsigned tileLoc = this->layout.at(i).at(j) % 0x64;

			unsigned x = tileLoc / 0xA;
			unsigned y = tileLoc % 0xA;

			bool isEmpty = (x + y) < 0x1;
			
			if (!isEmpty) vec->push_back(pos);
		}
	}

	for (size_t i = 0; i < vec->size(); i++) {
		this->tiles.at(i)->SetPosition(*vec->at(i)); 
		delete vec->at(i);
	}
	
	vec->clear();
	delete vec;
}
bool TileChunk::IsWithinBounds(CollisionRect& crect) const {
	return (crect.position.x + crect.size.x) > this->position.x || crect.position.x < (this->position.x + this->GetSize().x);
}
bool TileChunk::IsWithinView(const sf::View& view) const {
	return (this->position.x + this->GetSize().x) > (view.getCenter().x - view.getSize().x / 2);
}