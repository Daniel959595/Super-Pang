#include "MoveAble.h"

MoveAble::MoveAble(Resources::Objects object, Direction dir, sf::Time animationTime)
	//: GameObj(object, dir), m_dir(dir)
	: m_animation(Resources::instance().animationData(object), object, dir, m_sprite, animationTime), m_dir(dir)
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
