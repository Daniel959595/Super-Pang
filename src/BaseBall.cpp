#include "BaseBall.h"
#include "RegularBall.h"
#include "BreakableTile.h"

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
	//setVelocity(dir, isNewBall);
}

sf::Vector2f BaseBall::getScaleFactors(BallSize size) const
{
	/*float width = float((m_sprite.getTexture()->getSize().x));
	float height = float((m_sprite.getTexture()->getSize().y));*/
	float width  = m_sprite.getGlobalBounds().width;
	float height = m_sprite.getGlobalBounds().height;
	float factorX = getDesireSize(size) / width;
	float factorY = getDesireSize(size) / height;
	return sf::Vector2f(factorX, factorY);
}

float BaseBall::getDesireSize(BallSize size) const
{
	switch (size)
	{
	case BallSize::Big:    return BIG_BALL_SIZE;    break;
	case BallSize::Medium: return MEDIUM_BALL_SIZE; break;
	case BallSize::Small:  return SMALL_BALL_SIZE;  break;
	case BallSize::Tiny:   return TINY_BALL_SIZE;   break;
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

//void BaseBall::setVelocity(Direction dir, bool isNewBall)
//{
//	float y = (isNewBall ? -20.f : 0.f);
//	switch (dir)
//	{
//	case Direction::Right: m_velocity = sf::Vector2f(3.5f, y);  break;
//	case Direction::Left:  m_velocity = sf::Vector2f(-3.5f, y); break;	
//	default:
//		break;
//	}
//}

//void BaseBall::update(sf::Time delta)
//{
//	float dt = delta.asSeconds();
//	m_toatalTime += dt;
//	if (m_toatalTime >= m_moveTime) {
//		m_toatalTime = 0;
//		//m_velocity.y += m_gravity * dt;
//		m_velocity.y += m_gravity;
//		if (m_velocity.y > maxVelocity(m_ballSize))
//			m_velocity.y = maxVelocity(m_ballSize);
//		//m_sprite.move(m_velocity * dt * BallSpeed);
//		m_sprite.move(m_velocity);
//	}
//	
//}

float BaseBall::maxVelocity(BallSize size)
{
	switch (size)
	{
	case BallSize::Big:    return 31.f;
	case BallSize::Medium: return 27.f;
	case BallSize::Small:  return 23.f;
	case BallSize::Tiny:   return 19.f;

	default: return 0.f;
	}
}

void BaseBall::borderCollision(sf::RectangleShape& border)
{
	moveInside(border);
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
		m_velocity.y *= -1;
	}
	else
		return;

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
	case BallSize::Small:  return BallSize::Tiny;
	default:
		return BallSize::Big;
		break;
	}
}

void BaseBall::setQuartes(const GameObj& other)
{
	if (GameObj::isCollide(other))
		analizeCollision(other);	
}

bool BaseBall::isCollide() const
{
	if (m_quarters[0] == 1 || m_quarters[1] == 1 ||
		m_quarters[2] == 1 || m_quarters[3] == 1)
		return true;
	return false;
}

bool BaseBall::isCollide(const GameObj& other) const
{
	return GameObj::isCollide(other);
}

void BaseBall::analizeCollision(const GameObj& other)
{
	/*auto &thisRect  = this->getGlobalBounds();
	auto &otherRect = other.getHitBox();*/

	setQuartesPos();
	checkQuartes(other);

}

void BaseBall::setQuartesPos()
{
	auto& thisRect = this->getGlobalBounds();
	static auto size = sf::Vector2f(thisRect.width / 2, thisRect.height / 2);

	fstQurter = sf::FloatRect(sf::Vector2f(thisRect.left + (thisRect.width) / 2, thisRect.top), size);
	scdQurter = sf::FloatRect(sf::Vector2f(thisRect.left, thisRect.top), size);
	trdQurter = sf::FloatRect(sf::Vector2f(thisRect.left, thisRect.top + (thisRect.height / 2)), size);
	frtQurter = sf::FloatRect(sf::Vector2f(thisRect.left + (thisRect.width) / 2, thisRect.top + (thisRect.height / 2)), size);
}

void BaseBall::checkQuartes(const GameObj& other)
{
	auto thisRect  = this->getGlobalBounds();
	auto otherRect = other.getHitBox();

	if (fstQurter.intersects(otherRect) && scdQurter.intersects(otherRect)) {      // top collisoin.
		m_quarters[0] = 1; m_quarters[1] = 1;
	}
	else if (scdQurter.intersects(otherRect) && trdQurter.intersects(otherRect)) { // left collision.		
		m_quarters[1] = 1; m_quarters[2] = 1;
	}
	else if (trdQurter.intersects(otherRect) && frtQurter.intersects(otherRect)) { // bottom collision.
		m_quarters[2] = 1; m_quarters[3] = 1;
	}
	else if (frtQurter.intersects(otherRect) && fstQurter.intersects(otherRect)) { // right collision.
		m_quarters[3] = 1; m_quarters[0] = 1;
	}
	else if (fstQurter.intersects(otherRect)) {                                  // top right collision.
		if (isInRadius(other, TileCorner::DownLeft))
			m_quarters[0] = 1;
	}
	else if (scdQurter.intersects(otherRect)) {                                     // top left collision.
		if (isInRadius(other, TileCorner::DownRight))
			m_quarters[1] = 1;
	}
	else if (trdQurter.intersects(otherRect)) {                                     // bottom left collision.
		if (isInRadius(other, TileCorner::UpRight))
			m_quarters[2] = 1;
	}
	else if (frtQurter.intersects(otherRect)) {                                     // bottom right collision.
		if (isInRadius(other, TileCorner::UpLeft))
			m_quarters[3] = 1;
	}
}


bool BaseBall::isInRadius(const GameObj& other, TileCorner corner)
{
	auto otherBounds = other.getGlobalBounds();
	switch (corner)
	{
	case TileCorner::Middle:
		return true;
	case TileCorner::UpLeft:
		return checkDistance(sf::Vector2f(otherBounds.left, otherBounds.top)); 
	case TileCorner::UpRight:
		return checkDistance(sf::Vector2f(otherBounds.left + otherBounds.width, otherBounds.top)); 
	case TileCorner::DownLeft:
		return checkDistance(sf::Vector2f(otherBounds.left, otherBounds.top + otherBounds.height));
	case TileCorner::DownRight:
		return checkDistance(sf::Vector2f(otherBounds.left + otherBounds.width, otherBounds.top + otherBounds.height));
	
	default:
		return true;
	}
}

bool BaseBall::checkDistance(const sf::Vector2f corner)
{
	auto &thisBounds = this->getGlobalBounds();
	sf::Vector2f ballCenter = { thisBounds.left + (thisBounds.width / 2), thisBounds.top + (thisBounds.height / 2) };

	auto radius = thisBounds.width / 2;

	auto distance = std::sqrt((std::pow(ballCenter.x - corner.x,2)) + (std::pow(ballCenter.y - corner.y,2)));

	return (distance <= radius ? true:false);
}

void BaseBall::fixCollision()
{
	auto thisBounds = m_sprite.getGlobalBounds();
	m_newDirection = getNewDirect();
	switch (m_newDirection)
	{
	case MixDirection::Up:                    m_sprite.setPosition(thisBounds.left, thisBounds.top + m_velocity.y * -1);
		this->setDirection(Direction::Up);    m_velocity.y *= -1;															   break;
	case MixDirection::UpAndLeft:             m_sprite.setPosition(thisBounds.left, thisBounds.top + m_velocity.y * -1);
		this->setDirection(Direction::Up);    m_velocity.y *= -1; (m_velocity.x > 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::UpAndRight:            m_sprite.setPosition(thisBounds.left, thisBounds.top + m_velocity.y * -1);
		this->setDirection(Direction::Up);    m_velocity.y *= -1; (m_velocity.x < 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::Down:                  m_sprite.setPosition(thisBounds.left, thisBounds.top + m_velocity.y * -1);
		this->setDirection(Direction::Down);  m_velocity.y *= -1;															   break;
	case MixDirection::DownAndRight:          m_sprite.setPosition(thisBounds.left, thisBounds.top + m_velocity.y * -1);
		this->setDirection(Direction::Down);  m_velocity.y *= -1; (m_velocity.x < 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::DownAndLeft:           m_sprite.setPosition(thisBounds.left, thisBounds.top + m_velocity.y * -1);
		this->setDirection(Direction::Down);  m_velocity.y *= -1; (m_velocity.x > 0 ? m_velocity.x *= -1 : m_velocity.x *= 1); break;
	case MixDirection::Right:                 m_sprite.setPosition(thisBounds.left + m_velocity.x * -1, thisBounds.top);
		this->setDirection(Direction::Right); m_velocity.x *= -1;                                                              break;
	case MixDirection::Left:                  m_sprite.setPosition(thisBounds.left + m_velocity.x * -1, thisBounds.top);
		this->setDirection(Direction::Left);  m_velocity.x *= -1;															   break;
	default:
		break;
	}
	for (int i = 0; i < 4; i++) // func!!! resetQuarters()/
		m_quarters[i] = 0;
}

//void BaseBall::activateSound()
//{
//	Sounds::instance().activateSound(Sounds::Sound::BallExplosion);
//}

MixDirection BaseBall::getNewDirect()
{
	if (m_quarters[0] == 1 && m_quarters[1] == 1 && m_quarters[2] == 0 && m_quarters[3] == 0)      // top collision.
		return MixDirection::Down;
	else if (m_quarters[0] == 0 && m_quarters[1] == 1 && m_quarters[2] == 1 && m_quarters[3] == 0) // left collision.
		return MixDirection::Right;
	else if (m_quarters[0] == 0 && m_quarters[1] == 0 && m_quarters[2] == 1 && m_quarters[3] == 1) // down collision.
		return MixDirection::Up;
	else if (m_quarters[0] == 1 && m_quarters[1] == 0 && m_quarters[2] == 0 && m_quarters[3] == 1) // right collision.
		return MixDirection::Right;
	else if (m_quarters[0] == 1 && m_quarters[1] == 0 && m_quarters[2] == 0 && m_quarters[3] == 0) // top right collision.
		return (m_velocity.y >= 0 ? MixDirection::Left : MixDirection::DownAndLeft);
	else if (m_quarters[0] == 0 && m_quarters[1] == 1 && m_quarters[2] == 0 && m_quarters[3] == 0) // top left collision.
		return (m_velocity.y >= 0 ? MixDirection::Right : MixDirection::DownAndRight);
	else if (m_quarters[0] == 0 && m_quarters[1] == 0 && m_quarters[2] == 1 && m_quarters[3] == 0) // bottom left collision.
		return (m_velocity.y >= 0 ? MixDirection::UpAndRight : MixDirection::Right);
	else if (m_quarters[0] == 0 && m_quarters[1] == 0 && m_quarters[2] == 0 && m_quarters[3] == 1) // bottom right collision.
		return (m_velocity.y >= 0 ? MixDirection::UpAndLeft : MixDirection::Left);

	return MixDirection::Up; // should never reach here.
}
