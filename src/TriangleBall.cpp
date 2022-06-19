#include "TriangleBall.h"

//using pair = std::pair<std::shared_ptr<BaseBall>, std::shared_ptr<BaseBall>>;

const auto Angel = 5.f;

TriangleBall::TriangleBall(BallSize size, sf::Vector2f pos, Direction dir, bool isNewBall)
	: BaseBall(size, pos, Resources::Objects::TriangleBall, dir, isNewBall)
{
	setVelocity(dir, isNewBall);
	auto bounds = m_sprite.getLocalBounds();
}

void TriangleBall::setVelocity(Direction dir, bool isNewBall)
{
	float y = (isNewBall ? -11.f : 11.f);
	switch (dir)
	{
	case Direction::Right: m_velocity = sf::Vector2f(5.5f, y);  break;
	case Direction::Left:  m_velocity = sf::Vector2f(-5.5f, y); break;
	default:
		break;
	}
}

TriangleBall::pair TriangleBall::split()
{
	if (!this->isDisposed())
		return pair(); // exeption!!!

	auto first = std::make_shared<TriangleBall>(getSmallerSize(), m_sprite.getPosition(), Direction::Left, true);
	auto second = std::make_shared<TriangleBall>(getSmallerSize(), m_sprite.getPosition(), Direction::Right, true);
	pair newBalls(first, second);

	return newBalls;
}

void TriangleBall::update(sf::Time delta)
{
	float dt = delta.asSeconds();
	m_toatalTime += dt;
	if (m_toatalTime >= m_moveTime) {
		m_toatalTime = 0;
		//m_sprite.rotate(Angel);
		m_sprite.move(m_velocity);
	}
}

void TriangleBall::moveInside(sf::RectangleShape& border)
{
	sf::FloatRect bordBounds = border.getGlobalBounds();
	sf::FloatRect thisBounds = m_sprite.getGlobalBounds();
	if (thisBounds.left < bordBounds.left)                                             // left collision.
		m_velocity.x *= -1;
	else if (thisBounds.left + thisBounds.width > bordBounds.left + bordBounds.width)  // right collision.
		m_velocity.x *= -1;
	else if (thisBounds.top < bordBounds.top)                                          // top collision.
		m_velocity.y *= -1;
	else if (thisBounds.top + thisBounds.height > bordBounds.top + bordBounds.height) {  // down collision.
		m_velocity.y *= -1;
	}
	else 
		return;
	MoveAble::moveInside(border);
}

