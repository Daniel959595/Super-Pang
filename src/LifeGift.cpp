#include "LifeGift.h"

LifeGift::LifeGift(sf::Vector2f pos, Direction dir)
	: BaseGift(pos, Resources::LifeGift, dir)
{
	m_sprite.setScale(GIFT_SIZE / m_sprite.getGlobalBounds().width, GIFT_SIZE / m_sprite.getGlobalBounds().height);
}
