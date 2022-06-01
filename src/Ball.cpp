#include "Ball.h"

constexpr auto BallSpeed = 200.f;

Ball::Ball(BallSize size, sf::Vector2f pos, Direction dir)
	: m_ballSize(size), MoveAble(Resources::Objects::Ball, dir)
{
	m_sprite.setPosition(pos);
	m_sprite.setScale(getScaleFactors(size));
	//m_sprite.setColor(sf::Color(0, 255, 0));
	m_sprite.setColor(sf::Color(225, 0, 0));
	setVelocity(dir);
}

sf::Vector2f Ball::getScaleFactors(BallSize size) const
{
	float width = (m_sprite.getTexture()->getSize().x);
	float height = (m_sprite.getTexture()->getSize().y);
	float factorX = getDesireSize(size) / width;
	float factorY = getDesireSize(size) / height;
	return sf::Vector2f(factorX, factorY);
}

float Ball::getDesireSize(BallSize size) const
{
	switch (size)
	{
	case BallSize::Big:    return BIG_BALL_SIZE; break;
	//case BallSize::Medium: return MEDIUM_BALL_SIZE; break;
	//case BallSize::Small:  return SMALL_BALL_SIZE; break;
	default:
		break;
	}
	return 0.0f;
}

void Ball::setVelocity(Direction dir)
{
	//m_velocity = toVector(dir);
	m_velocity = { -2.f,0.f };
}

void Ball::update(sf::Time delta)
{
	float dt = delta.asSeconds();
	m_toatalTime += dt;
	if (m_toatalTime >= m_moveTime) {
		m_toatalTime = 0;
		//m_velocity.y += m_gravity * dt;
		m_velocity.y += m_gravity;

		//m_sprite.move(m_velocity * dt);
		m_sprite.move(m_velocity);
	}
	
}

void Ball::moveInside(sf::RectangleShape& border)
{
	sf::FloatRect bordBounds = border.getGlobalBounds();
	sf::FloatRect thisBounds = m_sprite.getGlobalBounds();
	if (thisBounds.left < bordBounds.left)                                             // left collision.
		m_velocity.x *= -1;
	else if (thisBounds.left + thisBounds.width > bordBounds.left + bordBounds.width)  // right collision.
		m_velocity.x *= -1;
	else if (thisBounds.top < bordBounds.top)                                          // top colllision.
		m_velocity.y *= -1;
	else if (thisBounds.top + thisBounds.height > bordBounds.top + bordBounds.height) {  // down collision.
		//m_velocity.y += m_gravity;
		m_velocity.y *= -1;
	}

	
	MoveAble::moveInside(border);
}