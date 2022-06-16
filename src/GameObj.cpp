#include "GameObj.h"

GameObj::GameObj(Resources::Objects object, Direction dir, sf::Time animationTime)
	: m_animation(Resources::instance().animationData(object), object, dir, m_sprite, animationTime)
{
}

void GameObj::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool GameObj::checkCollision(const GameObj& other) 
{
	//return other.isCollide(*this);
	return isCollide(other);
}

bool GameObj::isCollide(const GameObj& other) const
{
	auto thisRect = m_sprite.getGlobalBounds();
	auto otherRect = other.getGlobalBounds();
	if (thisRect.intersects(otherRect))
		return true;
	else
		return false;
}
