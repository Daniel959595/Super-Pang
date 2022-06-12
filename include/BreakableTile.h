#pragma once


#include "BaseTile.h"


class BreakableTile : public BaseTile
{
public:
	BreakableTile(TileColor color, TileSize size, sf::Vector2f pos, Direction dir);
	~BreakableTile() = default;
	
private:

};