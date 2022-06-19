#include "BaseShot.h"

constexpr auto ShotSpeed = 250.f;
const auto AnimationTime = sf::seconds(0.05f);

BaseShot::BaseShot(const sf::Vector2f& playerPos, Resources::Objects shotType)
	: MoveAble(shotType, Direction::Up, AnimationTime)
{
	setPosition(playerPos);
}

void BaseShot::setPosition(const sf::Vector2f& playerPos)
{
	sf::Vector2f pos = { playerPos.x + (32 / 3) * 2, playerPos.y - 8.f };
	m_sprite.setPosition(pos);
}

void BaseShot::update(sf::Time deltaTime)
{
	m_elapsed += deltaTime;
	m_animation.update(deltaTime);

	if (m_elapsed >= AnimationTime)
	{
		m_elapsed -= AnimationTime;
		m_sprite.move(sf::Vector2f(0, float(- 4 * (TABLE_HEIGHT / 191.f))));
	}
}


