#include "BaseBall.h"
#include "RegularBall.h"
#include <ctime>
#include <cmath>


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
	static std::vector<sf::Color> m_colors = { sf::Color(200,0,0),
										       sf::Color(0,200,0),
										       sf::Color(0,51,102),
										       sf::Color(102,0,51)};
	
	return m_colors[rand() % m_colors.size()];
}

void BaseBall::setVelocity(Direction dir, bool isNewBall)
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

BallSize BaseBall::getBallSize() const
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

bool BaseBall::isCollide(const GameObj& other) 
{
	if (GameObj::isCollide(other))
		return analizeCollision(other);
	return false;
}

bool BaseBall::analizeCollision(const GameObj& other)
{
	auto thisRect = this->getGlobalBounds();
	auto otherRect = other.getGlobalBounds();

	if (getNewDirect(other))
		return isInRadius(other);
	//fixCollision(other);
	return false;
}

bool BaseBall::getNewDirect(const GameObj& other)
{
	auto thisRect = this->getGlobalBounds();
	auto otherRect = other.getGlobalBounds();

	auto size = sf::Vector2f(thisRect.width / 2, thisRect.height / 2);

	auto fstQurter = sf::FloatRect(sf::Vector2f(thisRect.left + (thisRect.width) / 2, thisRect.top), size);
	auto scdQurter = sf::FloatRect(sf::Vector2f(thisRect.left, thisRect.top), size);
	auto trdQurter = sf::FloatRect(sf::Vector2f(thisRect.left, thisRect.top + (thisRect.height / 2)), size);
	auto frtQurter = sf::FloatRect(sf::Vector2f(thisRect.left + (thisRect.width) / 2, thisRect.top + (thisRect.height / 2)), size);

	m_newDirection = MixDirection::Unkown;

	if (fstQurter.intersects(otherRect) && scdQurter.intersects(otherRect)) // top collisoin.
		m_newDirection = MixDirection::Down;
	else if (fstQurter.intersects(otherRect) && frtQurter.intersects(otherRect)) // right collision.
		m_newDirection = MixDirection::Left;
	else if (fstQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			m_newDirection = MixDirection::Left;
		else
			m_newDirection = MixDirection::DownAndLeft;
	}
	else if (scdQurter.intersects(otherRect) && trdQurter.intersects(otherRect)) // left collision.
		m_newDirection = MixDirection::Right;
	else if (scdQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			m_newDirection = MixDirection::Right;
		else
			m_newDirection = MixDirection::DownAndRight;
	}
	else if (trdQurter.intersects(otherRect) && frtQurter.intersects(otherRect)) // bottom collision.
		m_newDirection = MixDirection::Up;
	else if (trdQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			m_newDirection = MixDirection::UpAndRight;
		else
			m_newDirection = MixDirection::Right;
	}
	else if (frtQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			m_newDirection = MixDirection::UpAndLeft;
		else
			m_newDirection = MixDirection::Left;
	}
	return (m_newDirection == MixDirection::Unkown ? false : true);
}

bool BaseBall::isInRadius(const GameObj& other)
{
	auto otherBounds = other.getGlobalBounds();
	switch (m_newDirection)
	{
	case MixDirection::Up:
	case MixDirection::Down:
		return true;
	case MixDirection::UpAndLeft:
		return checkDistance(sf::Vector2f(otherBounds.left, otherBounds.top)); 
	case MixDirection::UpAndRight:
		return checkDistance(sf::Vector2f(otherBounds.left + otherBounds.width, otherBounds.top)); 
	case MixDirection::DownAndLeft:
		return checkDistance(sf::Vector2f(otherBounds.left, otherBounds.top + otherBounds.height));
	case MixDirection::DownAndRight:
		return checkDistance(sf::Vector2f(otherBounds.left + otherBounds.width, otherBounds.top + otherBounds.height));
	case MixDirection::Right:
	case MixDirection::Left:
	case MixDirection::Unkown:
	default:
		return true;
	}
}

bool BaseBall::checkDistance(const sf::Vector2f corner)
{
	auto thisBounds = this->getGlobalBounds();
	sf::Vector2f ballCenter = { thisBounds.left + (thisBounds.width / 2), thisBounds.top + (thisBounds.height / 2) };

	auto radius = thisBounds.width / 2;

	auto distance = std::sqrt((std::pow(ballCenter.x - corner.x,2)) + (std::pow(ballCenter.y - corner.y,2)));

	return (distance <= radius ? true:false);
}

void BaseBall::fixCollision(const GameObj& other)
{
	auto thisBounds = m_sprite.getGlobalBounds();
	auto otherBounds = other.getGlobalBounds();

	switch (m_newDirection)
	{
	case MixDirection::Up:   m_sprite.setPosition(thisBounds.left, otherBounds.top - thisBounds.height);
		this->setDirection(Direction::Up);   m_velocity.y *= -1; break;
	case MixDirection::UpAndLeft:  m_sprite.setPosition(thisBounds.left, otherBounds.top - thisBounds.height);
		this->setDirection(Direction::Up);   m_velocity.y *= -1; (m_velocity.x > 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::UpAndRight: m_sprite.setPosition(thisBounds.left, otherBounds.top - thisBounds.height);
		this->setDirection(Direction::Up);   m_velocity.y *= -1; (m_velocity.x < 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::Down: m_sprite.setPosition(thisBounds.left, otherBounds.top + otherBounds.height);
		this->setDirection(Direction::Down); m_velocity.y *= -1; break;
	case MixDirection::DownAndRight: m_sprite.setPosition(thisBounds.left, otherBounds.top + otherBounds.height);
		this->setDirection(Direction::Down); m_velocity.y *= -1; (m_velocity.x < 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::DownAndLeft: m_sprite.setPosition(thisBounds.left, otherBounds.top + otherBounds.height);
		this->setDirection(Direction::Down); m_velocity.y *= -1; (m_velocity.x > 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::Right: m_sprite.setPosition(otherBounds.left + otherBounds.width, thisBounds.top);
		this->setDirection(Direction::Right); m_velocity.x *= -1; break;
	case MixDirection::Left: m_sprite.setPosition(otherBounds.left - thisBounds.width, thisBounds.top);
		this->setDirection(Direction::Left); m_velocity.x *= -1; break;
	default:
		break;
	}
}