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
