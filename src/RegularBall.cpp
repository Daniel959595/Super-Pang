#include "RegularBall.h"



RegularBall::RegularBall(BallSize size, sf::Vector2f pos, Direction dir, bool isNewBall)
	: BaseBall(size, pos, Resources::Objects::RegularBall, dir, isNewBall)
{
	setVelocity(dir, isNewBall);
}

void RegularBall::setVelocity(Direction dir, bool isNewBall)
{
	float y = (isNewBall ? -20.f : 0.f);
	switch (dir)
	{
	case Direction::Right: m_velocity = sf::Vector2f(3.5f, y);  break;
	case Direction::Left:  m_velocity = sf::Vector2f(-3.5f, y); break;
	default:
		break;
	}
}

RegularBall::pair RegularBall::split()
{
	if (!this->isDisposed())
		return pair(); // exeption!!!

	auto first  = std::make_shared<RegularBall>(getSmallerSize(), m_sprite.getPosition(), Direction::Left, true);
	auto second = std::make_shared<RegularBall>(getSmallerSize(), m_sprite.getPosition(), Direction::Right, true);
    pair newBalls(first, second);

	return newBalls;
}

void RegularBall::update(sf::Time delta)
{
	float dt = delta.asSeconds();
	m_toatalTime += dt;
	if (m_toatalTime >= m_moveTime) {
		m_toatalTime = 0;
		//m_velocity.y += m_gravity * dt;
		m_velocity.y += m_gravity;
		if (m_velocity.y > maxVelocity(m_ballSize))
			m_velocity.y = maxVelocity(m_ballSize);
		//m_sprite.move(m_velocity * dt * BallSpeed);
		m_sprite.move(m_velocity);
	}

}

