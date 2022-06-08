#include "GameObj.h"

//GameObj::GameObj(Resources::Objects object, Direction dir)
//	: m_animation(Resources::instance().animationData(object), object, dir, m_sprite)
//{
//}

GameObj::GameObj()
{

}

void GameObj::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool GameObj::checkCollision(const GameObj& other) const
{
	return other.isCollide(*this);
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
