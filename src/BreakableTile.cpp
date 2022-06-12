#include "BreakableTile.h"


BreakableTile::BreakableTile(TileColor color, TileSize size, sf::Vector2f pos, Direction dir)
	: BaseTile(color, size, pos, Resources::Objects::BreakableTile, dir)
{
}
