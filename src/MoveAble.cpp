#include "MoveAble.h"

MoveAble::MoveAble(Resources::Objects object, Direction dir, sf::Time animationTime)
	: GameObj(object, dir, animationTime), m_dir(dir)
	//: m_animation(Resources::instance().animationData(object), object, dir, m_sprite, animationTime), m_dir(dir)
{
}

void MoveAble::borderCollision(sf::RectangleShape& border)
{
	moveInside(border);
}

void MoveAble::moveInside(sf::RectangleShape& border)
{
	sf::FloatRect bordBounds = border.getGlobalBounds();
	sf::FloatRect thisBounds = m_sprite.getGlobalBounds();
	if (thisBounds.left <= bordBounds.left)                                             // left collision.
		m_sprite.setPosition(sf::Vector2f(bordBounds.left, thisBounds.top));
	else if (thisBounds.left + thisBounds.width >= bordBounds.left + bordBounds.width)  // right collision.
		m_sprite.setPosition(sf::Vector2f((bordBounds.left + bordBounds.width) - thisBounds.width, thisBounds.top));
	else if (thisBounds.top <= bordBounds.top)                                          // top colllision.
		m_sprite.setPosition(sf::Vector2f(thisBounds.left, bordBounds.top));
	else if (thisBounds.top + thisBounds.height >= bordBounds.top + bordBounds.height)  // down collision.
		m_sprite.setPosition(sf::Vector2f(thisBounds.left, (bordBounds.top + bordBounds.height) - thisBounds.height));
}

void MoveAble::analizeCollision(GameObj& other)
{
	auto thisRect  = this->getGlobalBounds();
	auto otherRect = other.getGlobalBounds();

	auto collisionSide = this->getCollisionSide(other);

	fixCollision(collisionSide, other);
}

MixDirection MoveAble::getCollisionSide(const GameObj& other)
{
	auto thisRect = this->getGlobalBounds();
	auto otherRect = other.getGlobalBounds();

	auto size = sf::Vector2f(thisRect.width / 2, thisRect.height / 2);

	auto fstQurter = sf::FloatRect(sf::Vector2f(thisRect.left + (thisRect.width) / 2, thisRect.top), size);
	auto scdQurter = sf::FloatRect(sf::Vector2f(thisRect.left, thisRect.top), size);
	auto trdQurter = sf::FloatRect(sf::Vector2f(thisRect.left, thisRect.top + (thisRect.height / 2)), size);
	auto frtQurter = sf::FloatRect(sf::Vector2f(thisRect.left + (thisRect.width) / 2, thisRect.top + (thisRect.height / 2)), size);

	if (fstQurter.intersects(otherRect) && scdQurter.intersects(otherRect)) // top collisoin.
		return MixDirection::Down;
	else if (fstQurter.intersects(otherRect) && frtQurter.intersects(otherRect)) // right collision.
		return MixDirection::Left;
	else if (fstQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			return MixDirection::Left;
		else
			return MixDirection::DownAndLeft;
	}
	else if (scdQurter.intersects(otherRect) && trdQurter.intersects(otherRect)) // left collision.
		return MixDirection::Right;
	else if (scdQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			return MixDirection::Right;
		else
			return MixDirection::DownAndRight;
	}
	else if (trdQurter.intersects(otherRect) && frtQurter.intersects(otherRect)) // bottom collision.
		return MixDirection::Up;
	else if (trdQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			return MixDirection::UpAndRight;
		else
			return MixDirection::Right;
	}
	else if (frtQurter.intersects(otherRect)) {
		if (m_velocity.y >= 0)
			return MixDirection::UpAndLeft;
		else
			return MixDirection::Left;
	}
}

void MoveAble::fixCollision(MixDirection newDir, const GameObj& other)
{
	auto thisBounds  = m_sprite.getGlobalBounds();
	auto otherBounds = other.getGlobalBounds();

	switch (newDir)
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

void MoveAble::setDirection(Direction newDir)
{
	m_dir = newDir;
	m_animation.direction(newDir);
}

