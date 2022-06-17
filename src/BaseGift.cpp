#include "BaseGift.h"

const auto AnimationTime = sf::seconds(0);

BaseGift::BaseGift(sf::Vector2f pos, Resources::Objects giftType, Direction dir)
	: MoveAble(giftType, dir, AnimationTime)
{
	m_giftType = giftType;
	m_sprite.setPosition(pos);
	//m_sprite.setScale(m_sprite.getGlobalBounds().width/ GIFT_SIZE, m_sprite.getGlobalBounds().height / GIFT_SIZE);
}

Resources::Objects BaseGift::getGiftType()
{
	return m_giftType;
}

void BaseGift::update(sf::Time delta)
{
	float dt = delta.asSeconds();
	m_toatalTime += dt;
	if (m_toatalTime >= m_moveTime) {
		m_toatalTime = 0;		
		m_sprite.move(0, m_gravity);
		m_animation.update(delta);
	}
}

void BaseGift::fixCollision(const GameObj& other)
{
	auto otherBounds = other.getGlobalBounds();
	auto thisBounds  = m_sprite.getGlobalBounds();
	sf::Vector2f pos = { thisBounds.left, otherBounds.top - thisBounds.height };
	m_sprite.setPosition(pos);
}
