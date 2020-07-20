#pragma once

#include <iostream>
#include "Tile.h"
#include "../../Collision/CollisionRect.h"
#include "../../Entities/Player.h"

class TileChunk 
{
public:

	unsigned tileSize;
	unsigned tileScale;

	bool hasGenerated;

	Player* player;

	sf::Texture* tileset;
	sf::Vector2f position;

	std::vector<std::vector<unsigned> > layout;
	std::vector<Tile*> tiles;

	TileChunk(void);
	TileChunk(const TileChunk& tchunk);
	~TileChunk(void);

	TileChunk& operator=(const TileChunk& tchunk);

	const sf::Vector2u& GetElementSize(void) const;
	const sf::Vector2f& GetSize(void) const;
	void GenerateTiles(unsigned&& tileSize, unsigned&& tileScale);
	void DrawChunk(sf::RenderTarget& target);
	void CheckPlayerCollision(void);
	void UpdatePosition(void);
	bool IsWithinBounds(CollisionRect& crect) const;
	bool IsWithinView(const sf::View& view) const;
};