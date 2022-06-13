#include "BreakableTile.h"


BreakableTile::BreakableTile(TileColor color, TileSize size, sf::Vector2f pos, Direction dir)
	: BaseTile(color, size, pos, Resources::Objects::BreakableTile, dir)
{
}

void BreakableTile::setIsDisposed(bool status)
{
	m_isBreaking = true;
}

void BreakableTile::update(sf::Time delta)
{
	if (!m_isBreaking)
		return;
	m_toatalTime += delta.asSeconds();
	if (m_toatalTime >= m_updateTime) {
		m_toatalTime = 0;
		static int i = 0;
		i++;
		if (i == 4)
			m_isDisposed = true;
		m_animation.update(delta);
	}
}
