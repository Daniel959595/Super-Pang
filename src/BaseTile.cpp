#include "BaseTile.h"


const auto AnimationTime = sf::seconds(0.02f);

BaseTile::BaseTile(TileColor color, TileSize size, sf::Vector2f pos, Resources::Objects tileType, Direction dir)
	: m_tileType(tileType), Unmovable(tileType, dir, AnimationTime)
{
	m_sprite.setPosition(pos);
	m_sprite.setScale(getScaleFactors(size));
	m_sprite.setColor(getColor(color));
}

sf::Color BaseTile::getColor(TileColor color)
{
	static std::vector<sf::Color> m_colors = { sf::Color(200,0,0),
											   sf::Color(0,120,0),
											   sf::Color(153,255,255),
											   sf::Color(102,0,51) };

	switch (color)
	{
	case TileColor::Blue:   return m_colors[1];
	case TileColor::Orange: return m_colors[3];
	case TileColor::Red:    return m_colors[0];
	default:
		return m_colors[1];
	}
}

sf::Vector2f BaseTile::getScaleFactors(TileSize size) const
{
	float width = float((m_sprite.getGlobalBounds().width));	
	float factor = getDesireSize(size) / width;

	return sf::Vector2f(factor, factor);       // same factor for both.
}

float BaseTile::getDesireSize(TileSize size) const
{
	switch (size)
	{
	case TileSize::Big:    return BIG_TILE_SIZE; break;
	case TileSize::Medium: return MEDIUM_TILE_SIZE; break;
	case TileSize::Small:  return SMALL_TILE_SIZE; break;
	default:
		break;
	}
	return 100.f;
}