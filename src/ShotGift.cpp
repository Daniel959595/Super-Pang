#include "ShotGift.h"

ShotGift::ShotGift(sf::Vector2f pos, Direction dir)
	: BaseGift(pos, Resources::ShotGift, dir)
{
	m_sprite.setScale(GIFT_SIZE / m_sprite.getGlobalBounds().width, GIFT_SIZE / m_sprite.getGlobalBounds().height);
}
