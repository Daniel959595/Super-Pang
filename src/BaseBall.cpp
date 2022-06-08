#include "BaseBall.h"
#include "RegularBall.h"
#include <ctime>


constexpr auto BallSpeed = 50.f;
const auto AnimationTime = sf::seconds(0.1f);

BaseBall::BaseBall(BallSize size, sf::Vector2f pos, Resources::Objects ballType, Direction dir, bool isNewBall)
	: m_ballSize(size), MoveAble(ballType, dir, AnimationTime), m_newBall(isNewBall)
{
	srand(unsigned(time(NULL)));
	m_sprite.setPosition(pos);
	m_sprite.setScale(getScaleFactors(size));
	m_sprite.setColor(getRandColor());
	setVelocity(dir, isNewBall);
}

sf::Vector2f BaseBall::getScaleFactors(BallSize size) const
{
	float width = float((m_sprite.getTexture()->getSize().x));
	float height = float((m_sprite.getTexture()->getSize().y));
	float factorX = getDesireSize(size) / width;
	float factorY = getDesireSize(size) / height;
	return sf::Vector2f(factorX, factorY);
}

float BaseBall::getDesireSize(BallSize size) const
{
	switch (size)
	{
	case BallSize::Big:    return BIG_BALL_SIZE; break;
	case BallSize::Medium: return MEDIUM_BALL_SIZE; break;
	case BallSize::Small:  return SMALL_BALL_SIZE; break;
	default:
		break;
	}
	return 0.0f;
}

sf::Color BaseBall::getRandColor() const
{
	std::vector<sf::Color> m_colors = { sf::Color(200,0,0),
										sf::Color(0,200,0),
										sf::Color(0,0,200) };
	
	return m_colors[rand() % m_colors.size()];
}

void BaseBall::setVelocity(Direction dir, bool isNewBall)
{
	float y = (isNewBall ? -20 : 0);
	switch (dir)
	{
	case Direction::Right: m_velocity = sf::Vector2f(3.5f, y);  break;
	case Direction::Left:  m_velocity = sf::Vector2f(-3.5f, y); break;	
	default:
		break;
	}
}

void BaseBall::update(sf::Time delta)
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

float BaseBall::maxVelocity(BallSize size)
{
	switch (size)
	{
	case BallSize::Big:    return 31.f;
	case BallSize::Medium: return 27.f;
	case BallSize::Small:  return 23.f;

	default: return 0.f;
	}
}

void BaseBall::moveInside(sf::RectangleShape& border)
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
		//m_velocity.y += m_gravity; // need to be fixed. 
		m_velocity.y *= -1;
	}

	
	MoveAble::moveInside(border);
}

BallSize BaseBall::getBallSize()
{
	return m_ballSize;
}

BallSize BaseBall::getSmallerSize()
{
	switch (m_ballSize)
	{
	case BallSize::Big:    return BallSize::Medium;
	case BallSize::Medium: return BallSize::Small;
	default:
		return BallSize::Big;
		break;
	}
}
